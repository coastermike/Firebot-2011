#include <p24HJ128GP210A.h>
#include "pins.h"

void Timer_Init(void) //set up timers and interrupts
{
	T1CONbits.TON = 0;
	T1CONbits.TCS = 0;
	T1CONbits.TGATE = 0;
	T1CONbits.TCKPS = 0b11;
	TMR1 = 0x00;
	PR1 = 0x4C4B;
	
	IPC0bits.T1IP = 0x01;
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
	
	T1CONbits.TON = 1;
	
}	

void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{
	LED1=~LED1;
	TMR1 = 0x00;
	IFS0bits.T1IF = 0;
}	
