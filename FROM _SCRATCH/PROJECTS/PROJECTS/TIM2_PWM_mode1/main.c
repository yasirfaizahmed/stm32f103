#include "usart_debug0.h"

int main(){
	
	//Clock, GPIO for Tx, USART1 setup (Tx only)
	RCC->CR |= RCC_CR_HSION;
	while( !(RCC->CR & RCC_CR_HSIRDY) );
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	//turn on Alternate functions
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
	
	USART1->BRR = 0x1d4c;	//9600 baudrate, 72MHz sys_clock
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;
	
	
	//TIM4 setup
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->PSC = 36000;	
	TIM4->ARR = 1000;		//2Hz
	
	//TIM4 channel_4 pin, PWM setups
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
	GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
	
	TIM4->CCER |= TIM_CCER_CC4E;	//Capture/Compare 4 output enable
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;	//PWM mode 1 
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE;		
	TIM4->CR1 |= TIM_CR1_ARPE;
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CCR4 = 500;	//DC = CCRx / ARR
	
	TIM4->CR1 |= TIM_CR1_CEN;		//Turning on the timer at the end
	
	
	while(1){
		printMsg("%d\r", TIM4->CNT);
	}
	
}

