/*  
	Universidad Aut�noma de Baja California
	Microcontroladores y Microprocesadores
	Jimenez Robles Luis Eduardo		01208396
	Pr�ctica 8a 
*/
#include <avr/io.h>
#define my_UBRR(bauds) 16000000/8/bauds-1

char UART0_getchar(void);
unsigned int atoi(char *str);
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
	//char numcad[10];
	uint16_t num;
	UART0_Init(0);
	UART0_puts("\n\rUniversidad Autonoma de Baja California\n\r Practica 8a");
	UART0_getchar();
	UART0_puts("\n\rIntroduce un n�mero:\n\r");
	//UART0_gets(cad);
	//UART0_puts(cad);
	itoa(cad,123,16);
	UART0_puts(cad);
	/*num = atoi(cad);
	itoa(cad,num,16);
	UART0_puts("\n\rHex:");
	UART0_puts(cad);
	itoa(cad,num,2);
	UART0_puts("\n\rBin:");
	UART0_puts(cad);
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
	unsigned int cociente, residuo,count = 0, i=0, j;
	char c;
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
		count++;
	}while( cociente != 0 );	
	*str= '\0';
	str -=count;
	j = count -1;
	
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
	
	
	/*while(**strAux != *str)
	{
		if(**strAux != *str)
		{
			c = **strAux;
			**strAux++ = *str;
			*str-- =  c;
		}
	}*/
}	
unsigned int atoi(char *str)
{
	unsigned int num = 0, exp = 1, val, count = 0;
	
	while(*str)
	{
		str++;
		count++;
	}
	
	do
	{
		val = *str-- - '0';
		num = num + (val * exp);
		exp = exp*10;	
		count--;
	}while(count != 0);
	
	return num;
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
	


