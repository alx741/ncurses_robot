;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (May 19 2014) (Linux)
; This file was generated Wed Jun 11 21:51:01 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4550
	radix	dec
	__config 0x300000, 0xf8
	__config 0x300001, 0x38
	__config 0x300002, 0xd9
	__config 0x300003, 0xfe
	__config 0x300005, 0x7d
	__config 0x300006, 0x9a
	__config 0x300008, 0xff
	__config 0x300009, 0xff
	__config 0x30000a, 0xff
	__config 0x30000b, 0xff
	__config 0x30000c, 0xff
	__config 0x30000d, 0xff


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_putchar
	global	_command
	global	_time
	global	_delay
	global	_uart_init
	global	_getchar
	global	_get_command
	global	_execute
	global	_mult
	global	_atoi
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrput1
	extern	__gptrget1
	extern	_SPPCFGbits
	extern	_SPPEPSbits
	extern	_SPPCONbits
	extern	_UFRMLbits
	extern	_UFRMHbits
	extern	_UIRbits
	extern	_UIEbits
	extern	_UEIRbits
	extern	_UEIEbits
	extern	_USTATbits
	extern	_UCONbits
	extern	_UADDRbits
	extern	_UCFGbits
	extern	_UEP0bits
	extern	_UEP1bits
	extern	_UEP2bits
	extern	_UEP3bits
	extern	_UEP4bits
	extern	_UEP5bits
	extern	_UEP6bits
	extern	_UEP7bits
	extern	_UEP8bits
	extern	_UEP9bits
	extern	_UEP10bits
	extern	_UEP11bits
	extern	_UEP12bits
	extern	_UEP13bits
	extern	_UEP14bits
	extern	_UEP15bits
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTDbits
	extern	_PORTEbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_LATDbits
	extern	_LATEbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_DDRDbits
	extern	_TRISDbits
	extern	_DDREbits
	extern	_TRISEbits
	extern	_OSCTUNEbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_CCP1ASbits
	extern	_ECCP1ASbits
	extern	_CCP1DELbits
	extern	_ECCP1DELbits
	extern	_BAUDCONbits
	extern	_BAUDCTLbits
	extern	_CCP2CONbits
	extern	_CCP1CONbits
	extern	_ECCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSPCON2bits
	extern	_SSPCON1bits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_HLVDCONbits
	extern	_LVDCONbits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_SPPDATA
	extern	_SPPCFG
	extern	_SPPEPS
	extern	_SPPCON
	extern	_UFRM
	extern	_UFRML
	extern	_UFRMH
	extern	_UIR
	extern	_UIE
	extern	_UEIR
	extern	_UEIE
	extern	_USTAT
	extern	_UCON
	extern	_UADDR
	extern	_UCFG
	extern	_UEP0
	extern	_UEP1
	extern	_UEP2
	extern	_UEP3
	extern	_UEP4
	extern	_UEP5
	extern	_UEP6
	extern	_UEP7
	extern	_UEP8
	extern	_UEP9
	extern	_UEP10
	extern	_UEP11
	extern	_UEP12
	extern	_UEP13
	extern	_UEP14
	extern	_UEP15
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_DDRD
	extern	_TRISD
	extern	_DDRE
	extern	_TRISE
	extern	_OSCTUNE
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_EECON1
	extern	_EECON2
	extern	_EEDATA
	extern	_EEADR
	extern	_RCSTA
	extern	_TXSTA
	extern	_TXREG
	extern	_RCREG
	extern	_SPBRG
	extern	_SPBRGH
	extern	_T3CON
	extern	_TMR3
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_CCP1AS
	extern	_ECCP1AS
	extern	_CCP1DEL
	extern	_ECCP1DEL
	extern	_BAUDCON
	extern	_BAUDCTL
	extern	_CCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_ECCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSPCON2
	extern	_SSPCON1
	extern	_SSPSTAT
	extern	_SSPADD
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_LVDCON
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC0	equ	0xfee
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1
r0x0a	res	1
r0x0b	res	1
r0x0c	res	1
r0x0d	res	1
r0x0e	res	1
r0x0f	res	1
r0x10	res	1
r0x11	res	1
r0x12	res	1
r0x13	res	1
r0x14	res	1
r0x15	res	1
r0x16	res	1
r0x17	res	1
r0x18	res	1
r0x19	res	1
r0x1a	res	1
r0x1b	res	1
r0x1c	res	1
r0x1d	res	1

udata_code_0	udata
_get_command_com_1_14	res	8

udata_code_1	udata
_atoi_values_1_24	res	8

udata_code_2	udata
_command	res	8

udata_code_3	udata
_time	res	4

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_code__main	code
_main:
;	.line	230; code.c	OSCCONbits.SCS1 = 1;
	BSF	_OSCCONbits, 1
;	.line	232; code.c	OSCCONbits.IRCF2 = 1;
	BSF	_OSCCONbits, 6
;	.line	233; code.c	OSCCONbits.IRCF1 = 1;
	BSF	_OSCCONbits, 5
;	.line	235; code.c	ADCON1 = 0x0F;
	MOVLW	0x0f
	MOVWF	_ADCON1
;	.line	238; code.c	uart_init();
	CALL	_uart_init
;	.line	242; code.c	TRISB = 0;
	CLRF	_TRISB
;	.line	243; code.c	PORTB = 0;
	CLRF	_PORTB
_00417_DS_:
;	.line	248; code.c	if( get_command(command) )
	MOVLW	HIGH(_command)
	MOVWF	r0x01
	MOVLW	LOW(_command)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_get_command
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x00, W
	IORWF	r0x01, W
	BZ	_00417_DS_
	BANKSEL	(_command + 4)
;	.line	251; code.c	time[0] = command[4];
	MOVF	(_command + 4), W, B
	BANKSEL	_time
	MOVWF	_time, B
	BANKSEL	(_command + 5)
;	.line	252; code.c	time[1] = command[5];
	MOVF	(_command + 5), W, B
	BANKSEL	(_time + 1)
	MOVWF	(_time + 1), B
	BANKSEL	(_command + 6)
;	.line	253; code.c	time[2] = command[6];
	MOVF	(_command + 6), W, B
	BANKSEL	(_time + 2)
	MOVWF	(_time + 2), B
	BANKSEL	(_command + 7)
;	.line	254; code.c	time[3] = command[7];
	MOVF	(_command + 7), W, B
	BANKSEL	(_time + 3)
	MOVWF	(_time + 3), B
	BANKSEL	_command
;	.line	256; code.c	if(command[0]=='x' && command[2]=='f')
	MOVF	_command, W, B
	XORLW	0x78
	BNZ	_00403_DS_
_00452_DS_:
	BANKSEL	(_command + 2)
	MOVF	(_command + 2), W, B
	XORLW	0x66
	BNZ	_00403_DS_
;	.line	257; code.c	execute(0x20, atoi(time)); //PIN 38
	MOVLW	HIGH(_time)
	MOVWF	r0x01
	MOVLW	LOW(_time)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_atoi
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x20
	MOVWF	POSTDEC1
	CALL	_execute
	MOVLW	0x04
	ADDWF	FSR1L, F
_00403_DS_:
	BANKSEL	_command
;	.line	258; code.c	if(command[0]=='x' && command[2]=='b')
	MOVF	_command, W, B
	XORLW	0x78
	BNZ	_00406_DS_
_00456_DS_:
	BANKSEL	(_command + 2)
	MOVF	(_command + 2), W, B
	XORLW	0x62
	BNZ	_00406_DS_
;	.line	259; code.c	execute(0x10, atoi(time)); //PIN 37
	MOVLW	HIGH(_time)
	MOVWF	r0x01
	MOVLW	LOW(_time)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_atoi
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x10
	MOVWF	POSTDEC1
	CALL	_execute
	MOVLW	0x04
	ADDWF	FSR1L, F
_00406_DS_:
	BANKSEL	_command
;	.line	260; code.c	if(command[0]=='y' && command[2]=='f')
	MOVF	_command, W, B
	XORLW	0x79
	BNZ	_00409_DS_
_00460_DS_:
	BANKSEL	(_command + 2)
	MOVF	(_command + 2), W, B
	XORLW	0x66
	BNZ	_00409_DS_
;	.line	261; code.c	execute(0x08, atoi(time)); //PIN 36
	MOVLW	HIGH(_time)
	MOVWF	r0x01
	MOVLW	LOW(_time)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_atoi
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x08
	MOVWF	POSTDEC1
	CALL	_execute
	MOVLW	0x04
	ADDWF	FSR1L, F
_00409_DS_:
	BANKSEL	_command
;	.line	262; code.c	if(command[0]=='y' && command[2]=='b')
	MOVF	_command, W, B
	XORLW	0x79
	BZ	_00464_DS_
	BRA	_00417_DS_
_00464_DS_:
	BANKSEL	(_command + 2)
	MOVF	(_command + 2), W, B
	XORLW	0x62
	BZ	_00466_DS_
	BRA	_00417_DS_
_00466_DS_:
;	.line	263; code.c	execute(0x04, atoi(time)); //PIN 35
	MOVLW	HIGH(_time)
	MOVWF	r0x01
	MOVLW	LOW(_time)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_atoi
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x04
	MOVWF	POSTDEC1
	CALL	_execute
	MOVLW	0x04
	ADDWF	FSR1L, F
	BRA	_00417_DS_
	RETURN	

; ; Starting pCode block
S_code__atoi	code
_atoi:
;	.line	177; code.c	unsigned int atoi(char* string)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x0a, POSTDEC1
	MOVFF	r0x0b, POSTDEC1
	MOVFF	r0x0c, POSTDEC1
	MOVFF	r0x0d, POSTDEC1
	MOVFF	r0x0e, POSTDEC1
	MOVFF	r0x0f, POSTDEC1
	MOVFF	r0x10, POSTDEC1
	MOVFF	r0x11, POSTDEC1
	MOVFF	r0x12, POSTDEC1
	MOVFF	r0x13, POSTDEC1
	MOVFF	r0x14, POSTDEC1
	MOVFF	r0x15, POSTDEC1
	MOVFF	r0x16, POSTDEC1
	MOVFF	r0x17, POSTDEC1
	MOVFF	r0x18, POSTDEC1
	MOVFF	r0x19, POSTDEC1
	MOVFF	r0x1a, POSTDEC1
	MOVFF	r0x1b, POSTDEC1
	MOVFF	r0x1c, POSTDEC1
	MOVFF	r0x1d, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
;	.line	180; code.c	unsigned int integer=0;
	CLRF	r0x03
	CLRF	r0x04
;	.line	183; code.c	for(i=0;i<4;i++)
	CLRF	r0x05
	CLRF	r0x06
	CLRF	r0x07
	CLRF	r0x08
	CLRF	r0x09
	CLRF	r0x0a
	CLRF	r0x0b
	CLRF	r0x0c
	CLRF	r0x0d
	CLRF	r0x0e
	CLRF	r0x0f
	CLRF	r0x10
	CLRF	r0x11
	CLRF	r0x12
	CLRF	r0x13
	CLRF	r0x14
	CLRF	r0x15
	CLRF	r0x16
	CLRF	r0x17
	CLRF	r0x18
	CLRF	r0x19
	CLRF	r0x1a
_00308_DS_:
;	.line	185; code.c	if( string[i] == '0' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x30
	BNZ	_00279_DS_
;	.line	186; code.c	values[i] = 0;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x07, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x08, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x00
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00279_DS_:
;	.line	187; code.c	if( string[i] == '1' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x31
	BNZ	_00281_DS_
;	.line	188; code.c	values[i] = 1;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x09, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x0a, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x01
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00281_DS_:
;	.line	189; code.c	if( string[i] == '2' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x32
	BNZ	_00283_DS_
;	.line	190; code.c	values[i] = 2;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x0b, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x0c, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x02
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00283_DS_:
;	.line	191; code.c	if( string[i] == '3' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x33
	BNZ	_00285_DS_
;	.line	192; code.c	values[i] = 3;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x0d, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x0e, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x03
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00285_DS_:
;	.line	193; code.c	if( string[i] == '4' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x34
	BNZ	_00287_DS_
;	.line	194; code.c	values[i] = 4;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x0f, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x10, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x04
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00287_DS_:
;	.line	195; code.c	if( string[i] == '5' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x35
	BNZ	_00289_DS_
;	.line	196; code.c	values[i] = 5;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x11, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x12, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x05
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00289_DS_:
;	.line	197; code.c	if( string[i] == '6' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x36
	BNZ	_00291_DS_
;	.line	198; code.c	values[i] = 6;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x13, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x14, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x06
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00291_DS_:
;	.line	199; code.c	if( string[i] == '7' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x37
	BNZ	_00293_DS_
;	.line	200; code.c	values[i] = 7;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x15, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x16, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x07
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00293_DS_:
;	.line	201; code.c	if( string[i] == '8' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x38
	BNZ	_00295_DS_
;	.line	202; code.c	values[i] = 8;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x17, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x18, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x08
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00295_DS_:
;	.line	203; code.c	if( string[i] == '9' )
	MOVF	r0x05, W
	ADDWF	r0x00, W
	MOVWF	r0x1b
	MOVF	r0x06, W
	ADDWFC	r0x01, W
	MOVWF	r0x1c
	CLRF	WREG
	BTFSC	r0x06, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x1d
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, PRODL
	MOVF	r0x1d, W
	CALL	__gptrget1
	MOVWF	r0x1b
	MOVF	r0x1b, W
	XORLW	0x39
	BNZ	_00309_DS_
;	.line	204; code.c	values[i] = 9;
	MOVLW	LOW(_atoi_values_1_24)
	ADDWF	r0x19, W
	MOVWF	r0x1b
	MOVLW	HIGH(_atoi_values_1_24)
	ADDWFC	r0x1a, W
	MOVWF	r0x1c
	MOVFF	r0x1b, FSR0L
	MOVFF	r0x1c, FSR0H
	MOVLW	0x09
	MOVWF	POSTINC0
	MOVLW	0x00
	MOVWF	INDF0
_00309_DS_:
;	.line	183; code.c	for(i=0;i<4;i++)
	MOVLW	0x02
	ADDWF	r0x07, F
	BTFSC	STATUS, 0
	INCF	r0x08, F
	MOVLW	0x02
	ADDWF	r0x09, F
	BTFSC	STATUS, 0
	INCF	r0x0a, F
	MOVLW	0x02
	ADDWF	r0x0b, F
	BTFSC	STATUS, 0
	INCF	r0x0c, F
	MOVLW	0x02
	ADDWF	r0x0d, F
	BTFSC	STATUS, 0
	INCF	r0x0e, F
	MOVLW	0x02
	ADDWF	r0x0f, F
	BTFSC	STATUS, 0
	INCF	r0x10, F
	MOVLW	0x02
	ADDWF	r0x11, F
	BTFSC	STATUS, 0
	INCF	r0x12, F
	MOVLW	0x02
	ADDWF	r0x13, F
	BTFSC	STATUS, 0
	INCF	r0x14, F
	MOVLW	0x02
	ADDWF	r0x15, F
	BTFSC	STATUS, 0
	INCF	r0x16, F
	MOVLW	0x02
	ADDWF	r0x17, F
	BTFSC	STATUS, 0
	INCF	r0x18, F
	MOVLW	0x02
	ADDWF	r0x19, F
	BTFSC	STATUS, 0
	INCF	r0x1a, F
	INFSNZ	r0x05, F
	INCF	r0x06, F
	MOVF	r0x06, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00390_DS_
	MOVLW	0x04
	SUBWF	r0x05, W
_00390_DS_:
	BTFSS	STATUS, 0
	BRA	_00308_DS_
;	.line	207; code.c	for(i=0;i<4;i++)
	CLRF	r0x00
	CLRF	r0x01
_00310_DS_:
;	.line	209; code.c	if(i==0)
	MOVF	r0x00, W
	IORWF	r0x01, W
	BNZ	_00300_DS_
;	.line	210; code.c	integer += mult(values[0], 1000);
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVLW	0xe8
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 1)
	MOVF	(_atoi_values_1_24 + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_atoi_values_1_24
	MOVF	_atoi_values_1_24, W, B
	MOVWF	POSTDEC1
	CALL	_mult
	MOVWF	r0x02
	MOVFF	PRODL, r0x05
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVF	r0x02, W
	ADDWF	r0x03, F
	MOVF	r0x05, W
	ADDWFC	r0x04, F
_00300_DS_:
;	.line	211; code.c	if(i==1)
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00391_DS_
	MOVF	r0x01, W
	BZ	_00392_DS_
_00391_DS_:
	BRA	_00302_DS_
_00392_DS_:
;	.line	212; code.c	integer += mult(values[1], 100);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x64
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 3)
	MOVF	(_atoi_values_1_24 + 3), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 2)
	MOVF	(_atoi_values_1_24 + 2), W, B
	MOVWF	POSTDEC1
	CALL	_mult
	MOVWF	r0x02
	MOVFF	PRODL, r0x05
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVF	r0x02, W
	ADDWF	r0x03, F
	MOVF	r0x05, W
	ADDWFC	r0x04, F
_00302_DS_:
;	.line	213; code.c	if(i==2)
	MOVF	r0x00, W
	XORLW	0x02
	BNZ	_00393_DS_
	MOVF	r0x01, W
	BZ	_00394_DS_
_00393_DS_:
	BRA	_00304_DS_
_00394_DS_:
;	.line	214; code.c	integer += mult(values[2], 10);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 5)
	MOVF	(_atoi_values_1_24 + 5), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 4)
	MOVF	(_atoi_values_1_24 + 4), W, B
	MOVWF	POSTDEC1
	CALL	_mult
	MOVWF	r0x02
	MOVFF	PRODL, r0x05
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVF	r0x02, W
	ADDWF	r0x03, F
	MOVF	r0x05, W
	ADDWFC	r0x04, F
_00304_DS_:
;	.line	215; code.c	if(i==3)
	MOVF	r0x00, W
	XORLW	0x03
	BNZ	_00395_DS_
	MOVF	r0x01, W
	BZ	_00396_DS_
_00395_DS_:
	BRA	_00311_DS_
_00396_DS_:
;	.line	216; code.c	integer += mult(values[3], 1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 7)
	MOVF	(_atoi_values_1_24 + 7), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_atoi_values_1_24 + 6)
	MOVF	(_atoi_values_1_24 + 6), W, B
	MOVWF	POSTDEC1
	CALL	_mult
	MOVWF	r0x02
	MOVFF	PRODL, r0x05
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVF	r0x02, W
	ADDWF	r0x03, F
	MOVF	r0x05, W
	ADDWFC	r0x04, F
_00311_DS_:
;	.line	207; code.c	for(i=0;i<4;i++)
	INFSNZ	r0x00, F
	INCF	r0x01, F
	MOVF	r0x01, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00397_DS_
	MOVLW	0x04
	SUBWF	r0x00, W
_00397_DS_:
	BTFSS	STATUS, 0
	BRA	_00310_DS_
;	.line	219; code.c	return integer;
	MOVFF	r0x04, PRODL
	MOVF	r0x03, W
	MOVFF	PREINC1, r0x1d
	MOVFF	PREINC1, r0x1c
	MOVFF	PREINC1, r0x1b
	MOVFF	PREINC1, r0x1a
	MOVFF	PREINC1, r0x19
	MOVFF	PREINC1, r0x18
	MOVFF	PREINC1, r0x17
	MOVFF	PREINC1, r0x16
	MOVFF	PREINC1, r0x15
	MOVFF	PREINC1, r0x14
	MOVFF	PREINC1, r0x13
	MOVFF	PREINC1, r0x12
	MOVFF	PREINC1, r0x11
	MOVFF	PREINC1, r0x10
	MOVFF	PREINC1, r0x0f
	MOVFF	PREINC1, r0x0e
	MOVFF	PREINC1, r0x0d
	MOVFF	PREINC1, r0x0c
	MOVFF	PREINC1, r0x0b
	MOVFF	PREINC1, r0x0a
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__mult	code
_mult:
;	.line	163; code.c	unsigned int mult(unsigned int a, unsigned int b)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
;	.line	165; code.c	unsigned int result=0;
	CLRF	r0x04
	CLRF	r0x05
;	.line	168; code.c	for(i=0;i<a;i++)
	CLRF	r0x06
	CLRF	r0x07
_00262_DS_:
	MOVF	r0x06, W
	MOVWF	r0x08
	MOVF	r0x07, W
	MOVWF	r0x09
	MOVF	r0x01, W
	SUBWF	r0x09, W
	BNZ	_00273_DS_
	MOVF	r0x00, W
	SUBWF	r0x08, W
_00273_DS_:
	BC	_00260_DS_
;	.line	170; code.c	result += b;
	MOVF	r0x02, W
	ADDWF	r0x04, F
	MOVF	r0x03, W
	ADDWFC	r0x05, F
;	.line	168; code.c	for(i=0;i<a;i++)
	INFSNZ	r0x06, F
	INCF	r0x07, F
	BRA	_00262_DS_
_00260_DS_:
;	.line	173; code.c	return result;
	MOVFF	r0x05, PRODL
	MOVF	r0x04, W
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__execute	code
_execute:
;	.line	154; code.c	void execute(unsigned int portb, unsigned int time_)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
;	.line	156; code.c	PORTB = 0;
	CLRF	_PORTB
;	.line	158; code.c	PORTB = portb;
	MOVF	r0x00, W
	MOVWF	_PORTB
;	.line	159; code.c	delay(time_);
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_delay
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
;	.line	160; code.c	PORTB = 0;
	CLRF	_PORTB
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__get_command	code
_get_command:
;	.line	119; code.c	int get_command(char* command)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
;	.line	123; code.c	putchar('>');
	MOVLW	0x3e
	MOVWF	POSTDEC1
	CALL	_putchar
	MOVF	POSTINC1, F
;	.line	125; code.c	for(i=0;i<8;i++)
	CLRF	r0x03
	CLRF	r0x04
_00173_DS_:
;	.line	127; code.c	com[i] = getchar();
	MOVLW	LOW(_get_command_com_1_14)
	ADDWF	r0x03, W
	MOVWF	r0x05
	MOVLW	HIGH(_get_command_com_1_14)
	ADDWFC	r0x04, W
	MOVWF	r0x06
	CALL	_getchar
	MOVWF	r0x07
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x07, INDF0
;	.line	125; code.c	for(i=0;i<8;i++)
	INFSNZ	r0x03, F
	INCF	r0x04, F
	MOVF	r0x04, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00229_DS_
	MOVLW	0x08
	SUBWF	r0x03, W
_00229_DS_:
	BNC	_00173_DS_
;	.line	133; code.c	if( (com[0]=='x' || com[0]=='y') && (com[1]==':') && (com[2]=='f' || com[2]=='b') && (com[3]==':')
	MOVFF	_get_command_com_1_14, r0x03
	MOVF	r0x03, W
	XORLW	0x78
	BZ	_00161_DS_
	MOVF	r0x03, W
	XORLW	0x79
	BZ	_00161_DS_
	BRA	_00159_DS_
_00161_DS_:
	BANKSEL	(_get_command_com_1_14 + 1)
	MOVF	(_get_command_com_1_14 + 1), W, B
	XORLW	0x3a
	BZ	_00235_DS_
	BRA	_00159_DS_
_00235_DS_:
	MOVFF	(_get_command_com_1_14 + 2), r0x03
	MOVF	r0x03, W
	XORLW	0x66
	BZ	_00164_DS_
	MOVF	r0x03, W
	XORLW	0x62
	BZ	_00164_DS_
	BRA	_00159_DS_
_00164_DS_:
	BANKSEL	(_get_command_com_1_14 + 3)
	MOVF	(_get_command_com_1_14 + 3), W, B
	XORLW	0x3a
	BZ	_00241_DS_
	BRA	_00159_DS_
_00241_DS_:
;	.line	135; code.c	&& (com[4]>0x2F && com[4]<0x3A) && (com[5]>0x2F && com[5]<0x3A) && (com[6]>0x2F && com[6]<0x3A) && (com[7]>0x2F && com[7]<0x3A) 
	MOVFF	(_get_command_com_1_14 + 4), r0x03
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x50
	BTFSS	STATUS, 0
	BRA	_00159_DS_
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x46
	BTFSC	STATUS, 0
	BRA	_00159_DS_
	MOVFF	(_get_command_com_1_14 + 5), r0x03
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x50
	BTFSS	STATUS, 0
	BRA	_00159_DS_
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x46
	BTFSC	STATUS, 0
	BRA	_00159_DS_
	MOVFF	(_get_command_com_1_14 + 6), r0x03
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x50
	BTFSS	STATUS, 0
	BRA	_00159_DS_
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x46
	BC	_00159_DS_
	MOVFF	(_get_command_com_1_14 + 7), r0x03
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x50
	BNC	_00159_DS_
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x46
	BC	_00159_DS_
;	.line	141; code.c	for(i=0;i<8;i++)
	CLRF	r0x03
	CLRF	r0x04
_00175_DS_:
;	.line	143; code.c	command[i] = com[i];
	MOVF	r0x03, W
	ADDWF	r0x00, W
	MOVWF	r0x05
	MOVF	r0x04, W
	ADDWFC	r0x01, W
	MOVWF	r0x06
	CLRF	WREG
	BTFSC	r0x04, 7
	SETF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x07
	MOVLW	LOW(_get_command_com_1_14)
	ADDWF	r0x03, W
	MOVWF	r0x08
	MOVLW	HIGH(_get_command_com_1_14)
	ADDWFC	r0x04, W
	MOVWF	r0x09
	MOVFF	r0x08, FSR0L
	MOVFF	r0x09, FSR0H
	MOVFF	INDF0, r0x08
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, PRODL
	MOVF	r0x07, W
	CALL	__gptrput1
;	.line	141; code.c	for(i=0;i<8;i++)
	INFSNZ	r0x03, F
	INCF	r0x04, F
	MOVF	r0x04, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00250_DS_
	MOVLW	0x08
	SUBWF	r0x03, W
_00250_DS_:
	BNC	_00175_DS_
;	.line	146; code.c	return 1;
	CLRF	PRODL
	MOVLW	0x01
	BRA	_00177_DS_
_00159_DS_:
;	.line	149; code.c	return 0;
	CLRF	PRODL
	CLRF	WREG
_00177_DS_:
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__getchar	code
_getchar:
;	.line	88; code.c	char getchar(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	91; code.c	if (RCSTAbits.OERR)
	BTFSS	_RCSTAbits, 1
	BRA	_00148_DS_
;	.line	94; code.c	RCSTAbits.CREN=0;
	BCF	_RCSTAbits, 4
;	.line	95; code.c	RCSTAbits.CREN=1;
	BSF	_RCSTAbits, 4
_00148_DS_:
;	.line	98; code.c	while( ! PIR1bits.RCIF );
	BTFSS	_PIR1bits, 5
	BRA	_00148_DS_
;	.line	100; code.c	return RCREG;
	MOVF	_RCREG, W
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__putchar	code
_putchar:
;	.line	79; code.c	void putchar(char c)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
_00138_DS_:
;	.line	81; code.c	while( ! PIR1bits.TXIF );
	BTFSS	_PIR1bits, 4
	BRA	_00138_DS_
;	.line	83; code.c	TXREG = c;
	MOVFF	r0x00, _TXREG
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__uart_init	code
_uart_init:
;	.line	34; code.c	void uart_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	39; code.c	SPBRG = 25; // 4MHz => 9600 baud (BRGH = 1)
	MOVLW	0x19
	MOVWF	_SPBRG
;	.line	42; code.c	TXSTAbits.BRGH = 1; // (1 = high speed)
	BSF	_TXSTAbits, 2
;	.line	45; code.c	BAUDCONbits.BRG16 = 0;
	BCF	_BAUDCONbits, 3
;	.line	48; code.c	TXSTAbits.SYNC = 0; // (0 = asynchrone)
	BCF	_TXSTAbits, 4
;	.line	51; code.c	RCSTAbits.SPEN = 1; // 1 = l port serie valide
	BSF	_RCSTAbits, 7
;	.line	54; code.c	PIE1bits.TXIE = 0; // 1 = interruption transmission valide
	BCF	_PIE1bits, 4
;	.line	57; code.c	TXSTAbits.TX9 = 0; // 0 = 8-bit transmis)
	BCF	_TXSTAbits, 6
;	.line	60; code.c	TXSTAbits.TXEN = 1; // (1 = transmission valide
	BSF	_TXSTAbits, 5
;	.line	63; code.c	PIE1bits.RCIE = 0; // 1 = interruption reception valide
	BCF	_PIE1bits, 5
;	.line	66; code.c	RCSTAbits.RX9 = 0; // 0 = 8-bit reception)
	BCF	_RCSTAbits, 6
;	.line	69; code.c	TRISCbits.TRISC6 = 1; // 0 = broche en sortie)
	BSF	_TRISCbits, 6
;	.line	70; code.c	TRISCbits.TRISC7 = 1; // 1 = broche en entree)
	BSF	_TRISCbits, 7
;	.line	73; code.c	RCSTAbits.CREN = 1; // 1 = reception valide
	BSF	_RCSTAbits, 4
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_code__delay	code
_delay:
;	.line	18; code.c	void delay(unsigned int delay)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	20; code.c	unsigned int a = 0;
	CLRF	r0x02
	CLRF	r0x03
;	.line	23; code.c	for(i=0;i<delay;i++)
	CLRF	r0x04
	CLRF	r0x05
_00110_DS_:
	MOVF	r0x01, W
	SUBWF	r0x05, W
	BNZ	_00127_DS_
	MOVF	r0x00, W
	SUBWF	r0x04, W
_00127_DS_:
	BC	_00112_DS_
;	.line	25; code.c	while(a < 10)
	MOVFF	r0x02, r0x06
	MOVFF	r0x03, r0x07
_00105_DS_:
	MOVLW	0x00
	SUBWF	r0x07, W
	BNZ	_00128_DS_
	MOVLW	0x0a
	SUBWF	r0x06, W
_00128_DS_:
	BC	_00107_DS_
;	.line	27; code.c	a = a+1;
	INFSNZ	r0x06, F
	INCF	r0x07, F
	BRA	_00105_DS_
_00107_DS_:
;	.line	29; code.c	a=0;
	CLRF	r0x02
	CLRF	r0x03
;	.line	23; code.c	for(i=0;i<delay;i++)
	INFSNZ	r0x04, F
	INCF	r0x05, F
	BRA	_00110_DS_
_00112_DS_:
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 2722 (0x0aa2) bytes ( 2.08%)
;           	 1361 (0x0551) words
; udata size:	   28 (0x001c) bytes ( 1.56%)
; access size:	   30 (0x001e) bytes


	end
