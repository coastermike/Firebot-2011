#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"
#include "stepper.h"
#include "adc_read.h"

unsigned int frontL = 0, frontR = 0, rightF = 0, rightR = 0, leftF = 0, leftR = 0, temp = 0;

void SetSpeed (int leftSpeed, int rightSpeed)
{
	PR2 = leftSpeed;
	PR3 = rightSpeed;
}

//sets speed and direction
//direction 0: Forward; 1: Backward
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR)
{
	Dir_L = dirL;
	Dir_R = dirR;
	PR2 = leftSpeed;
	PR3 = rightSpeed;
}

void SetTurn (int speed, char direction, char angle)
{
	resetDistances();
	if((direction = 0)) //CW
	{	
		SetSpeedDir (speed, 0, speed, 1);
	}
	else //CCW
	{
		SetSpeedDir (speed, 1, speed, 0);
	}
	while(getDistanceL() < angle){} //keep turning on angle is reached
	
	SetSpeed(0,0);
}

//follow right wall 
void FollowRightWall (unsigned int speed)
{
	frontL = Adc_IR(IR_FR_L);
	frontL = Adc_IR(IR_FR_L);
	LED1=~LED1;
	frontR = Adc_IR(IR_FR_R);
	frontR = Adc_IR(IR_FR_R);
	LED1=~LED1;
	rightF = Adc_IR(IR_RI_F);
	rightF = Adc_IR(IR_RI_F);
	LED1=~LED1;
	rightR = Adc_IR(IR_RI_R);
	rightR = Adc_IR(IR_RI_R);
	LED1=~LED1;
	leftF = Adc_IR(IR_LE_F);
	leftF = Adc_IR(IR_LE_F);
	LED1=~LED1;
	leftR = Adc_IR(IR_LE_R);
	leftR = Adc_IR(IR_LE_R);
	LED1=~LED1;
	
	if(frontL < 15 && frontR < 15)
	{
		SetTurn(20000, 1, 50);
		
		
	}	
	else if(frontL < 15 || frontR < 15)
	{
		SetSpeedDir(30000, 0, 10000, 0);
	}
	else if(rightF > 11)
	{
		SetSpeedDir(10000, 0, 25000, 0);
	}
	else if((rightF-rightR) < -1)
	{
		SetSpeedDir(25000, 0, 10000, 0);
	}
	else if((rightF-rightR) > 1)
	{
		SetSpeedDir(10000, 0, 25000, 0);
	}
	else
	{
		SetSpeedDir(10000, 0, 10000, 0);
	}	
}
