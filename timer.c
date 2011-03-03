#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"

//timer2-Left stepper
//timer3-Right Stepper
//timer4-relay PWM
//timer5-status LED
volatile unsigned int distanceL;
volatile unsigned int distanceR;

void Timer_Init(void) //set up timers and interrupts
{
	resetDistances();
	
	//disable interrupt nesting
	INTCON1bits.NSTDIS = 1;
	
	//setup timer5 for status LED
	T5CONbits.TON = 0;
	T5CONbits.TCS = 0;
	T5CONbits.TGATE = 0;
	T5CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR5 = 0x00;
	PR5 = 0x4C4B;	//Value to generate interrupt - 0.5sec
	
	//setup timer4 for relay PWM
	T4CONbits.TON = 0;
	T4CONbits.T32 = 0;
	T4CONbits.TCS = 0;
	T4CONbits.TGATE = 0;
	T4CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR4 = 0x00;
	PR4 = 0x0C4B;	//Value to generate interrupt - Xsec
	
	//setup timer2 for Left Stepper
	T2CONbits.TON = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TCS = 0;
	T2CONbits.TGATE = 0;
	T2CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR2 = 0x00;
	PR2 = 0x404B;	//Value to generate interrupt - Xsec
	
	//setup timer3 for Right Stepper
	T3CONbits.TON = 0;
	T3CONbits.TCS = 0;
	T3CONbits.TGATE = 0;
	T3CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR3 = 0x00;
	PR3 = 0xE04B;	//Value to generate interrupt - Xsec
	
	//Setup timer2 interrupt
	IPC1bits.T2IP = 4;
	IFS0bits.T2IF = 0;
	IEC0bits.T2IE = 1;
	
	//Setup timer3 interrupt
	IPC2bits.T3IP = 4;
	IFS0bits.T3IF = 0;
	IEC0bits.T3IE = 1;
	
	//Setup timer4 interrupt
	IPC6bits.T4IP = 3;
	IFS1bits.T4IF = 0;
	IEC1bits.T4IE = 1;
	
	//Setup timer5 interrupt
	IPC7bits.T5IP = 2;
	IFS1bits.T5IF = 0;
	IEC1bits.T5IE = 1;
	
	//Turn on timers
	T4CONbits.TON = 1;
	T5CONbits.TON = 1;
	T2CONbits.TON = 1;
	T3CONbits.TON = 1;
	
}	

//Left stepper
void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
{
	Step_L = ~Step_L;
	distanceL++;
	LED4=~LED4;
	IFS0bits.T2IF = 0;	
}

//Right stepper
void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void)
{
	Step_R = ~Step_R;
	distanceR++;
	LED3=~LED3;
	IFS0bits.T3IF = 0;
}	

//Relay
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
{
	LED2=~LED2;
	IFS1bits.T4IF = 0;
}
	
//Status LED, 1sec period
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{
	LED1=~LED1;
	IFS1bits.T5IF = 0;
}	

int getDistanceL(void)
{
	return distanceL;
}

int getDistanceR(void)
{
	return distanceR;
}

void resetDistances(void)
{
	distanceL = 0;
	distanceR = 0;
}
