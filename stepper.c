#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"
#include "stepper.h"

void StepperEnable (void)
{
	StepEn_L = 0;
	StepEn_R = 0;
}

void StepperDisable (void)
{
	StepEn_L = 1;
	StepEn_R = 1;
}	

//set microstep 0: Full Step, 1: Half Step
void SetMS (char LMS1, char RMS1)
{
	MS1_L = LMS1;
	MS1_R = RMS1;
}

void SetSpeed (int leftSpeed, int rightSpeed)
{
	TMR2 = 0x00;
	PR2 = leftSpeed;
	TMR3 = 0x00;
	PR3 = rightSpeed;
}

//sets speed and direction
//direction 0: CW; 1: CCW
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR)
{
	Dir_L = dirL;
	Dir_R = dirR;
	TMR2 = 0x00;
	PR2 = leftSpeed;
	TMR3 = 0x00;
	PR3 = rightSpeed;
}

void SetTurn (int speed, char direction, char angle)
{
	resetDistances();
	if((direction = 0)) //CW
	{	
		SetSpeedDir (speed, 1, speed, 1);
	}
	else
	{
		SetSpeedDir (speed, 0, speed, 0);
	}
	while(getDistanceL() < angle){} //keep turning on angle is reached
	
	SetSpeed(0,0);
}
