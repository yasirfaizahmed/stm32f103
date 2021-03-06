#include<stdint.h>  
#include"stm32f10x.h"
/*********
 1. Enable C port using IOPC bit from RCC_APB2ENR 
 2. Set the MODE[1:0] bits from GPIOx_CRH
 3. Use the ODR for output from GPIOx_ODR
 
 RCC base address  = 0x40021000
 GPIO base address = 0x40011000
**********/


#define RCC_APB2ENR	*(volatile uint32_t*) (RCC_BASE + 0x18)	//This means that RCC_APB2ENR is the value 
	//pointed by a int_32bit pointer whos value is RCC_BASE + offset address of RCC_APB2ENR.
#define GPIOC_CRH 	*(volatile uint32_t*)	(GPIOC_BASE + 0x04)
#define GPIOC_ODR		*(volatile uint32_t*)	(GPIOC_BASE + 0x0c)
	

int main(){
	
	RCC_APB2ENR |= (1<<4);
	GPIOC_CRH &= 0xFF0FFFFF;
	GPIOC_CRH |= 0x00200000;
	
	while(1){
		
		GPIOC_ODR |= (1<<13);
		for(int i=0;i<1000000;i++);
		GPIOC_ODR &= ~(1<<13);
		for(int i=0;i<1000000;i++);

	}
	

}
