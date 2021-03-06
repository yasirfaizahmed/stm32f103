#include "clock_config_basic.h"


/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/


void timer_config(){
	// 1. Enable the required timer form APBxENR 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	// 2. Set the prescalar for your in PSC register
	TIM2->PSC = 34-1;	// 8MHZ sys_clock / 8 ~~ 1us delay
	TIM2->ARR = 0xffff;	//max ARR value
		
	// 3. Enable TIMx, wait for it turn on
	TIM2->CR1 |= TIM_CR1_CEN;	//Enabling TIMx
	while(!(TIM2->SR & TIM_SR_UIF));	//// UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
	
	
}

void delay_us(uint32_t us){
	
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	************************************************/
	
	// 1. Reset the counter
	TIM2->CNT = 0;
	
	// 2. count till the delay value is reached with a wait time of iteration = 1us
	while(TIM2->CNT <= us);	//CNT increments at a rate of CK_CNT
	
	
}


void delay_ms (uint16_t ms)
{	
	
	for (uint16_t i=0; i<ms; i++)
	{
		delay_us (1000); // delay of 1 ms
	}
}

int main(){
	
	clock_config();
	
	timer_config();
	
	GPIO_config();
	
	
	
	while(1){
		for(uint16_t I=20;I<200;I++){
			GPIOC->ODR = (1<<13);
			delay_ms(100);
			GPIOC->ODR = (0<<13);
			delay_ms(I); 
		}
	}
	
}

