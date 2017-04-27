/*  
	Universidad Autónoma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Práctica 8a 
*/
#include <avr/io.h>
#include "UART.h"

int main(void) 
{ 
	char cad[20];
	uint16_t num;
	UART0_Init(0);
	while(1)
	{
		UART0_puts("\n\rUniversidad Autonoma de Baja California\n\r Practica 8a");
		UART0_puts("\n\n\rIntroduce un número:\n\r");
		UART0_gets(cad);
		num = atoi(cad);
		itoa(cad,num,10);
		UART0_puts("\n\rDec:");
		UART0_puts(cad);
		itoa(cad,num,2);
		UART0_puts("\n\rBin:");
		UART0_puts(cad);	
	}	
}


