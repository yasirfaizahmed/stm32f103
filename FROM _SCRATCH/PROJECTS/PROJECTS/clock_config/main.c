#include"stm32f10x.h"


	/*************>>>>>>> STEPS TO BE FOLLOWED <<<<<<<<************
	
	1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set
	
	********************************************************/
	
	
	/************>>>>>>> MY CUSTOM STEPS <<<<<<<***********
	
	1. No need of PLL, use 8MHz HSI as system clock, Enable it and wait for it become ready
	2. Configure the required PRESCALARS
	3. Select the HSI as system clock
	
	******************************************************/
	
void clock_config(void){
	//1. Enabeling HSI and waiting fot it to turn on
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC_CR_HSERDY));
		
	//2. Setting the AHB prescalar value
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;	//dividing the HSI with PRESCALAR value 1
		
	//3. Selecting HSI as system clock and witing for it to select 
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while(!(RCC_CFGR_SWS_HSI == RCC_CFGR_SW_HSI));
		
}

void GPIO_config(void){
	//1. Enabeling clock for IOPC 
	RCC->APB2ENR |= (1<<4);
	
	//2. selecting MODES, CNF 
	GPIOC->CRH &= 0xFF0FFFFF;	//Clearing pin 13 and keeping everything as it is
	GPIOC->CRH |= (2<<20);	//Setting MODE > 00 and CNF = 00 for General purpose output push-pull
	
}
	
int  main(){
	clock_config();
		
	GPIO_config();
	
	while(1){
		GPIOC->ODR |= (1<<13);
		for(int i=0;i<1000000;i++);
		GPIOC->ODR &= ~(1<<13);
		for(int i=0;i<1000000;i++);
		
	}
		
}
