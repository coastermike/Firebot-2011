#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"
#include "stepper.h"
#include "adc_read.h"

unsigned int frontL = 0, frontR = 0, rightF = 0, rightR = 0, leftF = 0, leftR = 0, temp = 0;

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
//	TMR2 = 0x00;
	PR2 = leftSpeed;
//	TMR3 = 0x00;
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

void FollowRightWall (unsigned int speed)
{
	temp = Adc_IR(IR_FR_L);
	frontL = temp;
	temp = Adc_IR(IR_FR_R);
	frontR = temp;
	rightF = Adc_IR(IR_RI_F);
	rightR = Adc_IR(IR_RI_R);
	leftF = Adc_IR(IR_LE_F);
	leftR = Adc_IR(IR_LE_R);
	
	if(frontL < 15 || frontR < 15)
	{
		SetSpeed(0,0);
	}
	else if(rightF > 11)
	{
		SetSpeed(10000, 20000);
	}
	else if((rightF-rightR) < -1)
	{
		SetSpeed(20000, 10000);
	}
	else if((rightF-rightR) > 1)
	{
		SetSpeed(10000, 20000);
	}
	else
	{
		SetSpeed(10000, 10000);
	}	
}
