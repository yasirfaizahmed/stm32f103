#include "stm32f10x.h"
#include <stdint.h>
#include "usart_debug0.h"
#include "GPIO_DRIVER1.h"



int main(){
	
	usart1_setup();
	
	//TIM4 setup
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 36000;	
	TIM2->ARR = 1000;		//2Hz
	TIM2->CR1 |= TIM_CR1_CEN;		//Turning on the timer at the end
	
	while(1){
		
		if((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF){
			printMsg("%d\r", TIM2->SR);
			TIM2->SR &= ~(TIM_SR_UIF);
			printMsg("%d\r", TIM2->SR);
		}
	}
	
	
	
}