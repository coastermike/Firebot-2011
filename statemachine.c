#include <p24HJ128GP210A.h>
#include "pins.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"

int state = 0;
unsigned int countLightL = 0, countLightR = 0, countLightRe = 0;

void stateOfMarvin()
{
	unsigned int fireL = 0, fireR = 0, fireM = 0, lightF_L = 0, lightF_R = 0, lightRe = 0;
	
	//always read light sensors
	lightF_L = Adc_Read(LIGHT_L);
	lightF_L = Adc_Read(LIGHT_L);
	lightF_R = Adc_Read(LIGHT_R);
	lightF_R = Adc_Read(LIGHT_R);
	lightRe = Adc_Read(LIGHT_RE);
	lightRe = Adc_Read(LIGHT_RE);
	
	//if in a room read fire sensors as well
	if(state == 1)
	{
		fireL = Adc_Read(FIRE_L);
		fireL = Adc_Read(FIRE_L);
		fireM = Adc_Read(FIRE_M);
		fireM = Adc_Read(FIRE_M);
		fireR = Adc_Read(FIRE_R);
		fireR = Adc_Read(FIRE_R);
	}
		
	if(state == 0)
	{
		if((lightF_L > getLightL() || lightF_R > getLightR()) && get_start_state() != 4)
		{
//			if(lightF_L > getLightL())
//			{
//				countLightL++;
//			}
//			else
//			{
//				countLightL = 0;
//			}		
			if(lightF_R > getLightR())
			{
				countLightR++;
			}
			else
			{
				countLightR = 0;
			}
			if( countLightR > 10)  //countLightL > 10 ||
			{
				state = 1; //starting to enter room one.
			}
			FollowRightWall(943);	
		}		
		else
		{
			FollowRightWall(943);
		}	
	}
	else if (state == 1)
	{
		SetSpeed(0,0);
		//move straight til rear sensor crosses
		
	}
	else if (state == 2)
	{
		//look for fire, move in, rotate 630degrees CW
	}	
	else if (state == 100)
	{
		SetSpeed(0,0);
		setBlackLightCalibration();
		state = 0;
	}	
	else
	{
		LEDError = 1;
	}		
}

void setMainState(char stateGoto)
{
	state = stateGoto;
}
