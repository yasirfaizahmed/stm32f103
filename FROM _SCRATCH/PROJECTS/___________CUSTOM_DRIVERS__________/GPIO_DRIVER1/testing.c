#include "GPIO_DRIVER1.h"

int main(){
	usart1_setup();
	
	pinMode(IOPB, GPIOB, 12, ip, ip_pupd);
	
	
	while(1){
		
		printMsg("%d\r", digitalReadpin(GPIOB, 12));
		for(int i=0;i<1500000;i++);

	}
	
}

