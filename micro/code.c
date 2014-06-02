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


void delay(void)
{
	unsigned int a = 0;

	while(a < 10000)
	{
		a = a+1;
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
	char com[13];

	for(i=0;i<13;i++)
	{
		com[i] = getchar();
	}

	//COMMAND VALIDATION
	//
	//<x,y>, <f,b>, special chars
	if( (com[0]=='x' || com[0]=='y') && (com[1]==':') && (com[2]=='f' || com[2]=='b') && (com[3]==':') && (com[8]==',')
	//duty cycle
	&& (com[4]>0x2F && com[4]<0x3A) && (com[5]>0x2F && com[5]<0x3A) && (com[6]>0x2F && com[6]<0x3A) && (com[7]>0x2F && com[7]<0x3A) 
	//time
	&& (com[9]>0x2F && com[9]<0x3A) && (com[10]>0x2F && com[10]<0x3A) && (com[11]>0x2F && com[11]<0x3A) 
	&& (com[12]>0x2F && com[12]<0x3A) )
	{
		//STRING COPY

		for(i=0;i<12;i++)
		{
			command[i] = com[i];
		}
		
		return 1;
	}

	return 0;
}





char command[13];

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


	TRISB = 0;
	PORTB = 0;


	while(1)
	{ 
		if( get_command(command) )
		{
		}

	}

}




