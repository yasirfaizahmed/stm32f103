#include "stm32f10x.h"
#include "usart_debug0.h"

uint16_t val;
uint16_t samples[2] = {0, 0};

int main(){
	//debug setup
	usart1_setup();
	
	//clock setup
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	
	//GPIO setup
	GPIOA->CRL |= GPIO_CRL_CNF5_1;
	GPIOA->CRL &= ~( GPIO_CRL_CNF5_0 );
	GPIOA->CRL |= GPIO_CRL_CNF7_1;
	GPIOA->CRL &= ~( GPIO_CRL_CNF7_0 );
	
	//interrupt setup
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);
	
	//ADC1 setup
	ADC1->SMPR2 |= ADC_SMPR2_SMP5_0 | ADC_SMPR2_SMP5_1 | ADC_SMPR2_SMP5_2;
	ADC1->SMPR2 |= ADC_SMPR2_SMP7_0 | ADC_SMPR2_SMP7_1 | ADC_SMPR2_SMP7_2;
	ADC1->SQR1 |= ADC_SQR1_L_0;
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	ADC1->SQR3 |= ADC_SQR3_SQ2_0 | ADC_SQR3_SQ2_1 | ADC_SQR3_SQ2_2;

	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_CONT;
	
	//turn on the DMA feature in ADC
	//ADC1->CR2 |= ADC_CR2_DMA;
	
	/*//DMA setup
	DMA1_Channel1->CPAR = (uint32_t)( &(ADC1->DR) );
	DMA1_Channel1->CMAR = (uint32_t)samples;
	DMA1_Channel1->CNDTR = 2;
	DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
	*/
	//turning on ADC1
	ADC1->CR2 |= ADC_CR2_ADON;
	for(int i=0;i<10000;i++);
	ADC1->CR2 |= ADC_CR2_ADON;
	for(int i=0;i<10000;i++);
	ADC1->CR2 |= ADC_CR2_CAL;
	while( (ADC1->CR2 & ADC_CR2_CAL) );
	
	
	while(1){
		//printMsg("ch5[%d] ch7[%d]\r",samples[0], samples[1] );
		
		printMsg("%d\r", val);
		for(int i=0;i<100000;i++);
		
	}

}


void ADC1_2_IRQHandler(void){
	if(ADC1->SR & ADC_SR_EOC){
		val = ADC1->DR;
	}
	
	 
}

