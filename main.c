/*  
	Universidad Aut�noma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Pr�ctica 8a 
*/
#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1

char UART0_getchar(void);
unsigned int cuentaChar(char *str);
void delay(void);
void escrito_line();
void itoa(char *str, uint16_t number, uint8_t base);
void invierteNumCad(char *str, int max);
void newLine();
void UART0_Init(uint16_t mode);
void UART0_gets(char *str);
void UART0_putchar(char data);
void UART0_puts(char *str);
void inMTTY();

int main(void) 
{ 
	char cad[20];
	char numcad[10];
	//uint16_t num;
	UART0_Init(0);
	inMTTY();
	UART0_gets(cad);
	escrito_line();
	UART0_puts(cad);
	itoa(numcad,239,10);
	newLine();
	UART0_puts(numcad);
	
	
	/*
	newLine();
	cuentaChar(numcad);
	newLine();
	invierteNumCad(numcad,cuentaChar(numcad));
	newLine();
	UART0_puts(numcad);
	*/
}
void delay(void) 
{ 
	volatile unsigned int i;
	for(i=0;i<0xffff;i++);
}
void UART0_Init(uint16_t mode)
{
	/*Funci�n para inicializar el puerto serie del ATmega1280/2560 
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
	unsigned int i=0;
	do{
		c = UART0_getchar();
		if( (i<=18)&&(c!=8)&&(c!=13) )
		{
			UART0_putchar(c);
			*str++ = c;
			i++;
		}
		if( (c==8) && (i>0) )
		{
			UART0_putchar('\b');
			UART0_putchar(' ');
			UART0_putchar(8);
			*str--='\0';
			i--;
		}
	}while(c != 13);
	*str = '\0';
}
void UART0_puts(char *str)
{
	while(*str)
	{
		UART0_putchar(*str++);
	}
}
void itoa(char *str, uint16_t number, uint8_t base)
{
	unsigned int cociente, residuo;
	unsigned char c;
	cociente = number;
	do{
		residuo = cociente%base;
		cociente = cociente/base;
		if(residuo > 9)
		{
			c = residuo + 55;
		}else{
			c = residuo + '0';
		}
		*str++ = c;
	}while( cociente != 0 );
	*str= '\0';
}
unsigned int atoi(char *str)
{
	unsigned int num = 0, exp = 1, val;
	while(*str)
	{
		*str++;
	}
	while(str != 0)
	{
		val = *--str - '0';
		num = num+ (val * exp);
		exp = exp*10;	
	}
	return num;
}

unsigned int cuentaChar(char *str)
{
	unsigned int cont = 0;
	unsigned char c;
	while(*str)
	{
		*str++;
		cont++;
	}
	c = cont + '0';
	newLine();
	UART0_putchar(' ');
	UART0_putchar(c);
	return cont;
}
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
void newLine(){
	UART0_putchar(10);
	UART0_putchar(13);
}
void escrito_line(){
	newLine();
	newLine();
	UART0_putchar('C');
	UART0_putchar('A');
	UART0_putchar('D');
	UART0_putchar('E');
	UART0_putchar('N');
	UART0_putchar('A');
	UART0_putchar(':');
	UART0_putchar(' ');
	newLine();
}
	


