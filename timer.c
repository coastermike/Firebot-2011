#include <p24HJ128GP210A.h>
#include "pins.h"

void Timer_Init(void) //set up timers and interrupts
{
	//disable interrupt nesting
	INTCON1bits.NSTDIS = 1;
	
	//set up timer 4 for status LED
	T4CONbits.TON = 0;
	T4CONbits.T32 = 0;
	T4CONbits.TCS = 0;
	T4CONbits.TGATE = 0;
	T4CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR4 = 0x00;
	PR4 = 0x4C4B;	//Value to generate interrupt - 0.5sec
	
	//setup timer2 for Left Stepper
	T2CONbits.TON = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TCS = 0;
	T2CONbits.TGATE = 0;
	T2CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR2 = 0x00;
	PR2 = 0x4C4B;	//Value to generate interrupt - 0.5sec
	
	//setup timer3 for Right Stepper
	T1CONbits.TON = 0;
	T1CONbits.TCS = 0;
	T1CONbits.TGATE = 0;
	T1CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR1 = 0x00;
	PR1 = 0x4C4B;	//Value to generate interrupt - 0.5sec
	
	//Setup timer2 interrupt
	IPC1bits.T2IP = 4;
	IFS0bits.T2IF = 0;
	IEC0bits.T2IE = 1;
	
	//Steup timer3 interrupt
	IPC2bits.T3IP = 4;
	IFS0bits.T3IF = 0;
	IEC0bits.T3IE = 1;
	
	//Setup timer4 interrupt
	IPC6bits.T4IP = 3;
	IFS1bits.T4IF = 0;
	IEC1bits.T4IE = 1;
	
	//Turn on timers
	T4CONbits.TON = 1;
	T2CONbits.TON = 1;
	T3CONbits.TON = 1;
	
}	

//Left stepper
void __attribute__((__interrupt__)) _T2Interrupt(void)
{
	
	IFS0bits.T2IF = 0;	
}

//Right stepper
void __attribute__((__interrupt__)) _T3Interrupt(void)
{
	
	IFS0bits.T3IF = 0;
}	

//Status LED, 1sec period
void __attribute__((__interrupt__)) _T4Interrupt(void)
{
	LED1=~LED1;
	IFS1bits.T4IF = 0;
}	
