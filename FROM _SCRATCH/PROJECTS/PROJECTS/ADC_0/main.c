#include "stm32f10x.h"
#include "usart_debug0.h"

uint16_t val = 0x0000;

int main(){
	
	usart1_setup();
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;	//enble the clock for ADC1, IOPA and AFIO
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;	//Max sys_clock/6 < 14MHz limit for ADC
	
	GPIOA->CRL |= GPIO_CRL_CNF5_1;	//input push-pull
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_0);	//clearing the default bit
	
	ADC1->CR1 |= ADC_CR1_EOCIE;	//enable EOC interrupt 
	NVIC_EnableIRQ(ADC1_2_IRQn);	//calling the interrupt handler
	
	ADC1->SMPR2 |= ADC_SMPR2_SMP5_0 | ADC_SMPR2_SMP5_1 | ADC_SMPR2_SMP5_2;	//239.5 cycles per second
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2; 	//channel 5 only
	ADC1->CR2 |= ADC_CR2_CONT;	//continious mode
	ADC1->CR2 |= ADC_CR2_ADON; 	//turnig ADC for the first time
	for(int i=0;i<10000;i++);	
	ADC1->CR2 |= ADC_CR2_ADON;	//turning ADC second time to actually turn it on
	for(int i=0;i<10000;i++);
	ADC1->CR2 |= ADC_CR2_CAL;	//calibrating
	for(int i=0;i<10000;i++);
	
	while(1){
		printMsg("ADC1_ch5:%d\r", val);
		
	}
	
	
	
}


void ADC1_2_IRQHandler(void){
	if(ADC1->SR & ADC_SR_EOC){
		val = ADC1->DR;
	}
	
}


