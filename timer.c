#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"
#include "start_command.h"
#include "statemachine.h"

//timer2-Left stepper
//timer3-Right Stepper
//timer4-relay PWM
//timer5-status LED
volatile unsigned int distanceL;
volatile unsigned int distanceR;
char switcher = 0;
char tempCount = 0;

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
	PR5 = 0xB896;	//Value to generate interrupt - 0.5sec
	
	//setup timer4 for relay PWM
	T4CONbits.TON = 0;
	T4CONbits.T32 = 0;
	T4CONbits.TCS = 0;
	T4CONbits.TGATE = 0;
	T4CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR4 = 0x00;
	PR4 = 0x004E;	//Value to generate interrupt - 2msec, x2BF = 18ms
	
	//setup timer6 to count stuff (like start switch timing)
	T6CONbits.TON = 0;
	T6CONbits.TON = 0;
	T6CONbits.T32 = 0;
	T6CONbits.TCS = 0;
	T6CONbits.TGATE = 0;
	T6CONbits.TCKPS = 0b11;	//prescaler 1:256
	TMR6 = 0x00;
	
	//setup timer2 for Left Stepper
	T2CONbits.TON = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TCS = 0;
	T2CONbits.TGATE = 0;
	T2CONbits.TCKPS = 0b00;	//prescaler 1:256
	TMR2 = 0x00;
	PR2 = 0x0000;	//Value to generate interrupt - Xsec
	
	//setup timer3 for Right Stepper
	T3CONbits.TON = 0;
	T3CONbits.TCS = 0;
	T3CONbits.TGATE = 0;
	T3CONbits.TCKPS = 0b00;	//prescaler 1:256
	TMR3 = 0x00;
	PR3 = 0x0000;	//Value to generate interrupt - Xsec
	
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
	
	//Setup timer6 interrupt
	IPC11bits.T6IP = 4;
	IFS2bits.T6IF = 0;
	IEC2bits.T6IE = 1;
	
	//Turn on timers
//	T4CONbits.TON = 1;
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
	if(switcher == 0)
	{
		PR4 = 0x02BF;
		RELAY = 0;
		switcher = 1;
	}
	else
	{
		PR4 = 0x004E;
		RELAY = 1;
		switcher = 0;
	}		
	IFS1bits.T4IF = 0;
}
	
//Status LED, 1sec period
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{
	LEDStatus=~LEDStatus;
	IFS1bits.T5IF = 0;
}	

void __attribute__((__interrupt__, no_auto_psv)) _T6Interrupt(void)
{
	if(get_start_state() == 1 && tempCount == 0)
	{
		tempCount = 0;
		set_start_state(0);
	}
	if(get_start_state() == 4 && tempCount == 0)
	{
		tempCount = 1;
	}
	else if (get_start_state() == 4 && tempCount == 1)
	{
		set_start_state(5);
		tempCount = 2;
		setMainState(100);
	}
//	else if (tempCount == 2)
//	{
//		tempCount = 3;
//	}
//	else if (tempCount == 3)
//	{
//		tempCount = 4;
//	}
//	else if (tempCount == 4)
//	{
//		tempCount = 5;
//	}
//	else if(tempCount == 5)
//	{
//		tempCount = 0;
//		setMainState(40);
//	}		
	IFS2bits.T6IF = 0;
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
