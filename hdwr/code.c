#include <pic18f4550.h>

__code char __at (__CONFIG1L) CONFIG1L = _PLLDIV_1_1L;
__code char __at (__CONFIG1H) CONFIG1H = _IESO_OFF_1H & _FCMEN_OFF_1H & _FOSC_INTOSCIO_EC_1H;
__code char __at (__CONFIG2L) CONFIG2L = _PWRT_OFF_2L & _BOR_OFF_2L & _VREGEN_OFF_2L;
__code char __at (__CONFIG2H) CONFIG2H = _WDT_OFF_2H;
__code char __at (__CONFIG3H) CONFIG3H = _MCLRE_OFF_3H & _PBADEN_OFF_3H & _CCP2MX_ON_3H;
__code char __at (__CONFIG4L) CONFIG4L = _DEBUG_OFF_4L & _STVREN_OFF_4L & _LVP_OFF_4L & _ICPRT_OFF_4L & _XINST_OFF_4L;
__code char __at (__CONFIG5L) CONFIG5L = _CP0_OFF_5L & _CP1_OFF_5L & _CP2_OFF_5L & _CP3_OFF_5L;
__code char __at (__CONFIG5H) CONFIG5H = _CPB_OFF_5H & _CPD_OFF_5H;
__code char __at (__CONFIG6L) CONFIG6L = _WRT0_OFF_6L & _WRT1_OFF_6L & _WRT2_OFF_6L & _WRT3_OFF_6L;
__code char __at (__CONFIG6H) CONFIG6H = _WRTC_OFF_6H & _WRTB_OFF_6H & _WRTD_OFF_6H;
__code char __at (__CONFIG7L) CONFIG7L = _EBTR0_OFF_7L & _EBTR1_OFF_7L & _EBTR2_OFF_7L & _EBTR3_OFF_7L;
__code char __at (__CONFIG7H) CONFIG7H = _EBTRB_OFF_7H;

void putchar(char c);

void delay(unsigned int delay)
{
	unsigned int a = 0;
	unsigned int i=0;

	for(i=0;i<delay;i++)
	{
		while(a < 10)
		{
			a = a+1;
		}
		a=0;
	}
}


void uart_init(void)
{

	// SPBRG - Baud Rate Generator Register
	//SPBRG = 129; // 20MHz => 9600 baud (BRGH = 1)
	SPBRG = 25; // 4MHz => 9600 baud (BRGH = 1)

	// BRGH - High Baud Rate Select Bit
	TXSTAbits.BRGH = 1; // (1 = high speed)

	// BAUD RATE GENERATOR 8 bits only (not 16 bits)
	BAUDCONbits.BRG16 = 0;

	// SYNC - USART Mode select Bit
	TXSTAbits.SYNC = 0; // (0 = asynchrone)

	// SPEN - Serial Port Enable Bit
	RCSTAbits.SPEN = 1; // 1 = l port serie valide

	// TXIE - USART Transmit Interupt Enable Bit
	PIE1bits.TXIE = 0; // 1 = interruption transmission valide

	// TX9 - 9-bit Transmit Enable Bit
	TXSTAbits.TX9 = 0; // 0 = 8-bit transmis)

	// TXEN - Transmit Enable Bit
	TXSTAbits.TXEN = 1; // (1 = transmission valide

	// RCIE - USART Receive Interupt Enable Bit
	PIE1bits.RCIE = 0; // 1 = interruption reception valide

	// RX9 - 9-bit Receive Enable Bit
	RCSTAbits.RX9 = 0; // 0 = 8-bit reception)

	// TRISC 6,7 set for UART USE
	TRISCbits.TRISC6 = 1; // 0 = broche en sortie)
	TRISCbits.TRISC7 = 1; // 1 = broche en entree)

	// CREN - Continuous Receive Enable Bit
	RCSTAbits.CREN = 1; // 1 = reception valide


}


void putchar(char c)
{
	while( ! PIR1bits.TXIF );

	TXREG = c;
	  
}


char getchar(void)
{

	if (RCSTAbits.OERR)
	{
		//IN CASE OF ERROR RESET CREN
		RCSTAbits.CREN=0;
		RCSTAbits.CREN=1;
	}

	while( ! PIR1bits.RCIF );

	return RCREG;

}


/* Returns 1 if valid command has loaded in COM
 *
 * COMMAND syntax (13 chars): 
 *
 * 	<x,y>:<f,b>:xxxx,yyyy
 *
 * 	x = X axis
 * 	y = Y axis
 * 	f = forward
 * 	b = backward
 * 	xxxx = duty cycle
 * 	yyyy = time
 *
 */ 
int get_command(char* command)
{
	int i=0;
	char com[8];
	putchar('>');

	for(i=0;i<8;i++)
	{
		com[i] = getchar();
	}

	//COMMAND VALIDATION
	//
	//<x,y>, <f,b>, special chars
	if( (com[0]=='x' || com[0]=='y') && (com[1]==':') && (com[2]=='f' || com[2]=='b') && (com[3]==':')
	//time
	&& (com[4]>0x2F && com[4]<0x3A) && (com[5]>0x2F && com[5]<0x3A) && (com[6]>0x2F && com[6]<0x3A) && (com[7]>0x2F && com[7]<0x3A) 
	)

	{
		//STRING COPY

		for(i=0;i<8;i++)
		{
			command[i] = com[i];
		}
		
		return 1;
	}

	return 0;
}



void execute(unsigned int portb, unsigned int time_)
{
	PORTB = 0;

	PORTB = portb;
	delay(time_);
	PORTB = 0;
}

unsigned int mult(unsigned int a, unsigned int b)
{
	unsigned int result=0;
	int i=0;

	for(i=0;i<a;i++)
	{
		result += b;
	}

	return result;
}


unsigned int atoi(char* string)
{
	int i=0;
	unsigned int integer=0;
	unsigned int values[4];

	for(i=0;i<4;i++)
	{
		if( string[i] == '0' )
			values[i] = 0;
		if( string[i] == '1' )
			values[i] = 1;
		if( string[i] == '2' )
			values[i] = 2;
		if( string[i] == '3' )
			values[i] = 3;
		if( string[i] == '4' )
			values[i] = 4;
		if( string[i] == '5' )
			values[i] = 5;
		if( string[i] == '6' )
			values[i] = 6;
		if( string[i] == '7' )
			values[i] = 7;
		if( string[i] == '8' )
			values[i] = 8;
		if( string[i] == '9' )
			values[i] = 9;
	}

	for(i=0;i<4;i++)
	{
		if(i==0)
			integer += mult(values[0], 1000);
		if(i==1)
			integer += mult(values[1], 100);
		if(i==2)
			integer += mult(values[2], 10);
		if(i==3)
			integer += mult(values[3], 1);
	}
	
	return integer;
}



char command[8];
char time[4];

void main(void)
{
	//INTERNAL OSCIOLATOR ENABLE
	OSCCONbits.SCS1 = 1;
	//4Mhz INTERNAL OSCILATOR CONFIG
	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	//ALL PINS ARE DIGITAL
	ADCON1 = 0x0F;

	//UART INIT
	uart_init();


	//PORTB INIT
	TRISB = 0;
	PORTB = 0;


	while(1)
	{ 
		if( get_command(command) )
		{

			time[0] = command[4];
			time[1] = command[5];
			time[2] = command[6];
			time[3] = command[7];

			if(command[0]=='x' && command[2]=='f')
				execute(0x20, atoi(time)); //PIN 38
			if(command[0]=='x' && command[2]=='b')
				execute(0x10, atoi(time)); //PIN 37
			if(command[0]=='y' && command[2]=='f')
				execute(0x08, atoi(time)); //PIN 36
			if(command[0]=='y' && command[2]=='b')
				execute(0x04, atoi(time)); //PIN 35
		}

	}

}




