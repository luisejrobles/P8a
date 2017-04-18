/*  Universidad Autonoma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	
	Practica 8a */

#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1
void delay(void);
char UART0_getchar(void);
void UART0_putchar(char data);
void UART0_Init(uint16_t mode);

int main(void) 
{ 
	//char cad[20];
	//uint16_t num;
	UART0_Init(0);
	UART0_putchar('E');
	UART0_putchar('D');
	UART0_putchar('U');
}

void delay(void) 
{ 
	volatile unsigned int i;
	for(i=0;i<0xffff;i++);
}

void UART0_Init(uint16_t mode)
{
	/*Función para inicializar el puerto serie del ATmega1280/2560 
	  Si mode es 0    9600,8,N,1
	  Si mode es 1    19200,8,N,1 */
	UCSR0A = (1<<U2X0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
	if(!mode)
	{
		my_UBRR(9600);
	}else if(mode)
	{
		my_UBRR(19200);
	}
	UBRRH0 = (unsigned char)(UBRR0 >> 8);
	UBRRL0 = (unsigned char)(UBRR0);
}

char UART0_getchar(void)
{	
	while(!(UCSR0A&(1<<RXC0)))
	{
		return UDR0;
	}
}

void UART0_putchar(char data)
{
	while(!(UCSR0A&(1<<UDRE0)))
	{
		UDR0 = data;
	}
}

void UART0_gets(char *str)
{
}

void UART0_puts(char *str)
{
}

void itoa(char *str, uint16_t number, uint8_t base)
{
}

/*unsigned int atoi(char *str)
{
}*/


