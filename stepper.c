#include <p24HJ128GP210A.h>
#include "pins.h"

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
	PR2 = leftSpeed;
	PR3 = rightSpeed;
}

//sets speed and direction
//direction 0: CW; 1: CCW
void SetSpeedDir (int leftSpeed, bit dirL, int rightSpeed, bit dirR)
{
	Dir_L = dirL;
	Dir_R = dirR;
	PR2 = leftSpeed;
	PR3 = rightSpeed;
}

void SetTurn (int speed, bit direction, char angle)
{
	stepcount = 0;
	if(direction = 0) //CW
	{	
		SetSpeedDir (speed, 1, speed, 1);
	}
	else
	{
		SetSpeedDir (speed, 0, speed, 0);
	}
	while(stepcount < angle){}
	
	SetSpeed(0,0);
}

			