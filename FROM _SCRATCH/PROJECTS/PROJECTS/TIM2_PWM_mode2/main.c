#include "stm32f10x.h"

int main(){
	
	//Clock setup
	RCC->APB1ENR |=  RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	
	//GPIO pin setup
	GPIOB->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
	GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
	
	//Timer setup
	TIM4->PSC = 72;
	TIM4->ARR = 1000;
	
	TIM4->CCER |= TIM_CCER_CC4E;	//Capture/Compare 4 output enable
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 ;	//PWM mode 2
	TIM4->CR1 |= TIM_CR1_ARPE;	//not really rewuired
	TIM4->EGR |= TIM_EGR_UG;	//not really required 
	//TIM4->CCER |= TIM_CCER_CC4P; // can also be used as PWM mode 2
	TIM4->CCR4 |= 200;
	TIM4->CR1 |= TIM_CR1_CEN;	
	
}

