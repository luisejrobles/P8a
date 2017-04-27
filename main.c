/*  
	Universidad Autónoma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Práctica 8a 
*/
#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1

char UART0_getchar(void);
unsigned int atoi(char *str);
void delay(void);
void itoa(char *str, uint16_t number, uint8_t base);
void push(char c);
void UART0_Init(uint16_t mode);
void UART0_gets(char *str);
void UART0_putchar(char data);
void UART0_puts(char *str);
void inMTTY();
 
int main(void) 
{ 
	char cad[20];
	//char numcad[10];
	uint16_t num;
	UART0_Init(0);
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
	UCSR0A = (1<<U2X0);		//Usart double speed
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|~(1<<UCSZ02); // Reception enable | Transmission enable | 9bit disable
	UCSR0C = (3<<UCSZ00);	//8bit enable
	if(!mode)
	{
		UBRR0 = 207;	//9600 baud rate UBRR
		
	}else if(mode)
	{
		UBRR0 = 103;	//19.2k baud rate UBRR
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
		if( (i<=18)&&(c!=8)&&(c!=13) )	//validacion menor al fin del arreglo, backspace y enter
		{
			UART0_putchar(c);
			*str++ = c;
			i++;
		}
		if( (c==8) && (i>0) )		//validacion backspace
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
	unsigned int cociente, residuo,count = 0, i=0, j;
	char c;
	cociente = number;
	do{
		residuo = cociente%base;
		cociente = cociente/base;
		if(residuo > 9)	//si es mayor a 9, agregar el respectivo para imprimir letra.
		{
			c = residuo + 55;
		}else{
			c = residuo + '0'; //agregar el respectivo para crear el caracter de numero
		}
		*str++ = c;
		count++;
	}while( cociente != 0 );	
	*str= '\0';
	str -=count;
	j = count -1;
	//==============invertir cadena==================
	while(i < j)
	{
		if( *(str+i) != *(str+j))
		{
			c = *(str+i);
			*(str+i) = *(str+j);
			*(str+j) = c;	
		}
		i++;
		j--;
	}
}	
unsigned int atoi(char *str)
{
	unsigned int num = 0, exp = 1, val, count = 0;
	//contando digitos en la cadena============
	while(*str)
	{
		str++;
		count++;
	}
	str--;	//no tomando en cuenta '\0'
	while(count != 0)
	{
		val = *str--;	//tomando el valor
		val = val - '0';	//obteniendo valor crudo
		num = num + (val * exp);	//almacenando valor crudo*exp en num
		exp = exp*10;
		count--;	
	}
	return num;
}
	


