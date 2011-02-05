#include <p24HJ128GP210A.h>
#include "pins.h"
#include "init.h"


#define On_Time  0xffff
#define Off_Time  0xffff
#define Pause_Time  0xffff


int main(void)
{
	
	int i=0;
//	OSCCON=OSCCON | 0b0000001000000001;
	Pin_Init();
	PORTG = 0xF000;
	for(i=0; i<On_Time;i++) 
	{
//		_asm
//			nop
//		_endasm
	}
	while (1)
	{
		PORTG = 0x1000;
			for(i=0; i<On_Time;i++) 
	{
//		_asm
//			nop
//		_endasm
	}
		PORTG = 0x2000;
	for(i=0; i<On_Time;i++) 
	{
//		_asm
//			nop
//		_endasm
	}
		PORTG = 0x4000;
	for(i=0; i<On_Time;i++) 
	{
//		_asm
//			nop
//		_endasm
	}
		PORTG = 0x8000;
	for(i=0; i<On_Time;i++) 
	{
//		_asm
//			nop
//		_endasm
	}

		

//		StepEN = 0;
//		StepDIR = 0;
//		MS1=0;
//		do
//		{
//			for(i=0;i<30000;i++){LED3 =1;
//			Step=0;}
//			for(i=0;i<30000;i++){LED3=0;
//			Step=1;}
//		}while (0);	
	}
}	
