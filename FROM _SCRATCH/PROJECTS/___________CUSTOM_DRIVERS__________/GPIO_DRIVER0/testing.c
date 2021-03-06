#include "GPIO_DRIVER0.h"

int main(){
	
	usart1_setup();	//for debugging
	
	pinMode(IOPC, GPIOC, 13, op_50MHz, op_gppp) ;
	
	while(1){
		
		GPIOC->ODR |= (1<<13);
		for(int i=0;i<1000000;i++);
		GPIOC->ODR &= ~(1<<13);
		for(int i=0;i<1000000;i++);

	}
	
}

