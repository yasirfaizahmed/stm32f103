#ifndef GPIO_DRIVER0_H_INCLUDED
#define GPIO_DRIVER0_H_INCLUDED

#include "stm32f10x.h"
#include <stdint.h>
//for debugging
#include "usart_debug0.h"


/*************** IOPx values*************************/
typedef enum{
	IOPA = (uint32_t)0x00000004,
	IOPB = (uint32_t)0x00000008,
	IOPC = (uint32_t)0x00000010,
	IOPD = (uint32_t)0x00000020,
	IOPE = (uint32_t)0x00000040,
	IOPF = (uint32_t)0x00000080,
	IOPG = (uint32_t)0x00000100,
	
}IOP;

/*************** MODE[1:0] values*************************/
typedef enum{
	//MODE{1:0}
	ip 			= 	(uint32_t)0x00000000,
	
	op_10MHz = 	(uint32_t)0x00000001, 
	op_2MHz  = 	(uint32_t)0x00000002,
	op_50MHz = 	(uint32_t)0x00000003
}MODE;

/*************** CNF[1:0] values*************************/
typedef enum{
	//CNF[1:0]
	ip_analog   =		(uint32_t)0x00000000,
	ip_floating = 	(uint32_t)0x00000001,
	ip_pupd     = 	(uint32_t)0x00000002,
	
	op_gppp			=  	(uint32_t)0x00000000,
	op_gpod			= 	(uint32_t)0x00000001,
	op_afpp			= 	(uint32_t)0x00000002,
	op_afod			= 	(uint32_t)0x00000003
}CNF;


void pinMode(IOP IOP_value, GPIO_TypeDef* port, int pin, MODE mode_value, CNF cnf_value){
	
	RCC->APB2ENR |= IOP_value;
	
	uint32_t final_value = mode_value | (cnf_value<<2);	//getting the fianl value of the the modes combined
	
	if(pin <= 7){
		port->CRL &= ~( (uint32_t)(4<<(4*pin)) );	//clearing the default reset bit
		port->CRL |= ( final_value<<(4*pin) );	//writing in CRL 
	}
	
	if(pin > 7){
		port->CRH &= ~( (uint32_t)(4<<4*(pin-8)) );	//clearing the default reset bit
		port->CRH |= ( final_value<<(4*(pin-8)) );	//writing in CRH
	}
	
}


	


#endif

