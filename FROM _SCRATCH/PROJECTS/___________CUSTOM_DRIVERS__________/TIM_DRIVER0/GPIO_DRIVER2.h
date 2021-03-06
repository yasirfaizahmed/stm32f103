#ifndef GPIO_DRIVER0_H_INCLUDED
#define GPIO_DRIVER0_H_INCLUDED

#include "stm32f10x.h"
#include <stdint.h>
//for debugging
#include "usart_debug0.h"

/************************************************RCC->APB2ENR bit definition*******************************************/
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



/***********************************************RCC->CRH, CRL bit definition****************************************/
/*************** MODE[1:0] values*************************/
typedef enum{
	//input values
	ip 			= 	(uint32_t)0x00000000,
	//output values
	op_10MHz = 	(uint32_t)0x00000001, 
	op_2MHz  = 	(uint32_t)0x00000002,
	op_50MHz = 	(uint32_t)0x00000003
}MODE;

/*************** CNF[1:0] values*************************/
typedef enum{
	//input values
	ip_analog   =		(uint32_t)0x00000000,
	ip_floating = 	(uint32_t)0x00000001,
	ip_pupd     = 	(uint32_t)0x00000002,
	//output values
	op_gppp			=  	(uint32_t)0x00000000,
	op_gpod			= 	(uint32_t)0x00000001,
	op_afpp			= 	(uint32_t)0x00000002,
	op_afod			= 	(uint32_t)0x00000003
}CNF;



/*********************************************GPIOx->ODR bit definition***********************************************/
typedef enum{
	LOW = 0, 
	HIGH = 1
}state;



/***************************************pin_mode function***********************************************/
void pin_mode(IOP IOP_value, GPIO_TypeDef* port, int pin, MODE mode_value, CNF cnf_value){
	
	RCC->APB2ENR |= IOP_value;
	
	uint32_t final_value = mode_value | (cnf_value<<2);	//getting the fianl value of the the modes combined
	
	if(pin <= 7){
		port->CRL &= ~( (uint32_t)(0xf<<(4*pin)) );	//clearing the default bits
		port->CRL |= ( final_value<<(4*pin) );	//writing in CRL 
	}
	
	if(pin > 7){
		port->CRH &= ~( (uint32_t)(0xf<<4*(pin-8)) );	//clearing the default bits
		port->CRH |= ( final_value<<(4*(pin-8)) );	//writing in CRH
	}
	
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////not working for pin number < 7 in port B//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************digital_write function ****************************************/
void digital_writepin(GPIO_TypeDef *port, int pin, state state_value){
	if(state_value == HIGH){
		port->ODR |= ( state_value<<pin );	//writing 1
	}
	else{
		port->ODR &=  ~(~state_value<<pin);	//writing 0
	}
	
}



/**********************************digital_lockpin function ****************************************/
void digital_lock(GPIO_TypeDef *port, int pin){
	if((port->LCKR & GPIO_LCKR_LCKK) == 1){	//if lock bit is set, reset it to remap the sequence 
		port->LCKR |= GPIO_LCKR_LCKK;
		port->LCKR &= ~(GPIO_LCKR_LCKK);	//To modify the bit, this is the sequence
		port->LCKR |= GPIO_LCKR_LCKK;
		
		port->LCKR &= ~(GPIO_LCKR_LCKK);	//finally clearing the LCKK bit
	}
	
	port->LCKR |= (1<<pin);
	
	port->LCKR |= GPIO_LCKR_LCKK;
	port->LCKR &= ~(GPIO_LCKR_LCKK);	//To modify the bit, this is the sequence
	port->LCKR |= GPIO_LCKR_LCKK;
	
	port->LCKR |= GPIO_LCKR_LCKK;	//finally locking the sequence
	
}


/**************************************digital_read function ******************************************/
state digital_readpin(GPIO_TypeDef *port, int pin){
	uint16_t mask = ( 1<<pin );
	if((port->IDR & mask) == mask){	//reading 1
		return HIGH;
	}
	else if((port->IDR & mask) == 0){	//reading 0
		return LOW;
	}
	return LOW;
}
	




#endif

