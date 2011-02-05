#include "pins.h"
#include <p24HJ128GP210A.h>

//Sets the Tris bits of the pins that are not part of a peripheral
void Pin_Init()
{
	//setting all Tris bits
	LED1Tris = 0;
	LED2Tris = 0;
	LED3Tris = 0;
	LED4Tris = 0;
	
	MS1Tris = 0;
	ENTris = 0;
	DIRTris = 0;
	StepTris = 0;
}
