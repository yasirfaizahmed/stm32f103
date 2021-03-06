#include "usart_debug0.h"
#include "GPIO_DRIVER2.h"

int main(){
	pin_mode(IOPA, GPIOA, 3, op_50MHz, op_gppp);
	
	digital_writepin(GPIOA, 3, HIGH);
	digital_lock(GPIOA, 3);
	digital_writepin(GPIOA, 3, LOW);
	
	
}