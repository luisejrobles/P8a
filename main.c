/*  
	Universidad Autónoma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Práctica 8a 
*/
#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1

char pop( void );
char UART0_getchar(void);
unsigned int cuentaChar(char *str);
void delay(void);
void escrito_line();
void itoa(char *str, uint16_t number, uint8_t base);
void invierteNumCad(char *str, int max);
void newLine();
void push(char c);
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
	unsigned int cociente, residuo, cont = 0;
	unsigned char c;
	cociente = number;
	/*
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
	*/
	while(cociente != 0)
	{
		residuo = cociente%base;
		cociente = cociente/base;
		cont++;
	}
	cont++;
	
	residuo = 0;
	cociente = number;
	str = str + cont;
	*str = '\0';
	do{
		residuo = cociente%base;
		cociente = cociente/base;
		if(residuo > 9)
		{
			c = residuo + 55;
			}else{
			c = residuo + '0';
		}
		*--str = c;
	}while(cociente !=0);
	
	/*do{
		residuo = cociente%base;
		cociente = cociente/base;
		if(residuo > 9)
		{
			c = residuo + 55;
			}else{
			c = residuo + '0';
		}
		push(c);
		cont++;
	}while( cociente != 0 );
	
	while(cont != 0)
	{
		*str++ = pop();	
		cont--;
	}
	*str='\0';*/
}
/*void push(char c)
{
	asm push bp
	asm mov bp,sp
	asm mov al,[bp+4]
	asm push ax
	
	asm pop bp
}
char pop( void )
{
	asm pop ax
}*/
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
	


