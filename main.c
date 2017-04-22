/*  
	Universidad Autónoma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Práctica 8a 
*/

#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1

char UART0_getchar(void);
void delay(void);
void UART0_Init(uint16_t mode);
void UART0_gets(char *str);
void UART0_putchar(char data);
void UART0_puts(char *str);
void inMTTY();

int main(void) 
{ 
	char cad[20];
	uint16_t num;
	UART0_Init(0);
	
	UART0_getchar();
	inMTTY();
	
	UART0_putchar(10);
	UART0_putchar(13);
	UART0_gets(cad);
	
	UART0_putchar(10);
	UART0_putchar(10);
	UART0_putchar(13);
	
	UART0_putchar('E');
	
	UART0_putchar(10);
	UART0_putchar(13);
	UART0_puts(cad);

	//==============================
	UART0_putchar(10);
	UART0_putchar(10);
	UART0_putchar(10);
	UART0_putchar(13);
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
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|~(1<<UCSZ02);
	UCSR0C = (3<<UCSZ00);
	if(!mode)
	{
		UBRR0 = 207;
		
	}else if(mode)
	{
		UBRR0 = 103;
	}
}

char UART0_getchar(void)
{	
	while ( !(UCSR0A & (1<<RXC0)) );
	putchar(UDR0);
	return UDR0;
	
}

void UART0_putchar(char data)
{
	while ( !(UCSR0A & (1<<UDRE0)) );	
	UDR0 = data;
}

void UART0_gets(char *str)
{
	unsigned char c;
	
	do{
		c = UART0_getchar();
		if(c != 10)
		{
			*str++ = c;
			//*str++;
		}
	}while(c != 10);
	
	*str++ = '\0';
}

void UART0_puts(char *str)
{
	while(*str)
	{
		putchar(*str++);
	}
}

void itoa(char *str, uint16_t number, uint8_t base)
{
}

/*unsigned int atoi(char *str)
{
}*/

void inMTTY()
{
	UART0_putchar('U');
	UART0_putchar('N');
	UART0_putchar('I');
	UART0_putchar('V');
	UART0_putchar('E');
	UART0_putchar('R');
	UART0_putchar('S');
	UART0_putchar('I');
	UART0_putchar('D');
	UART0_putchar('A');
	UART0_putchar('D');
	UART0_putchar(' ');
	UART0_putchar('A');
	UART0_putchar('U');
	UART0_putchar('T');
	UART0_putchar('O');
	UART0_putchar('N');
	UART0_putchar('O');
	UART0_putchar('M');
	UART0_putchar('A');
	UART0_putchar(' ');
	UART0_putchar('D');
	UART0_putchar('E');
	UART0_putchar(' ');
	UART0_putchar('B');
	UART0_putchar('A');
	UART0_putchar('J');
	UART0_putchar('A');
	UART0_putchar(' ');
	UART0_putchar('C');
	UART0_putchar('A');
	UART0_putchar('L');
	UART0_putchar('I');
	UART0_putchar('F');
	UART0_putchar('O');
	UART0_putchar('R');
	UART0_putchar('N');
	UART0_putchar('I');
	UART0_putchar('A');
	UART0_putchar(10);
	UART0_putchar(13);	
	UART0_putchar('P');
	UART0_putchar('R');
	UART0_putchar('A');
	UART0_putchar('C');
	UART0_putchar('T');
	UART0_putchar('I');
	UART0_putchar('C');
	UART0_putchar('A');
	UART0_putchar(' ');
	UART0_putchar('8');
	UART0_putchar('a');
	UART0_putchar(10);
	UART0_putchar(13);
}


