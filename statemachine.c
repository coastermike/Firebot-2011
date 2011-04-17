#include <p24HJ128GP210A.h>
#include "pins.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"
#include "timer.h"

unsigned int state = 0, comingfrom = 0, spray = 0;
unsigned int countLightL = 0, countLightR = 0, countLightRe = 0;
const unsigned int NORMSPEED = 943;

void stateOfMarvin()
{
	unsigned int fireL = 0, fireR = 0, fireM = 0, lightF_R = 0, lightRe = 0;
	unsigned int frontLe = 0, frontRi = 0, leftFr = 0, rightFr = 0;
	//always read light sensors
	lightF_R = Adc_Read(LIGHT_R);
	lightF_R = Adc_Read(LIGHT_R);
	LED1=~LED1;
	lightRe = Adc_Read(LIGHT_RE);
	lightRe = Adc_Read(LIGHT_RE);
	LED1=~LED1;
	
	//if in a room read fire sensors as well
	if(state == 200 || state == 201)
	{
		fireL = Adc_Read(FIRE_L);
		fireL = Adc_Read(FIRE_L);
		LED1=~LED1;
		fireM = Adc_Read(FIRE_M);
		fireM = Adc_Read(FIRE_M);
		LED1=~LED1;
		fireR = Adc_Read(FIRE_R);
		fireR = Adc_Read(FIRE_R);
		LED1=~LED1;
		leftFr = Adc_IR(IR_LE_F);
		leftFr = Adc_IR(IR_LE_F);
		LED1=~LED1;
		rightFr = Adc_IR(IR_RI_F);
		rightFr = Adc_IR(IR_RI_F);
		LED1=~LED1;
	}
	
	if(state == 0)
	{
		SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
	}
	else if(state == 1)
	{
		resetDistances();
		SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
		while(getDistanceL() < 600){};
		SetTurn(800, 0, 98);
		resetDistances();
		SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
		while(getDistanceL() < 1700){};
		state = 40;
	}	
	else if(state == 40)
	{
		if((lightF_R > getLightR()) && get_start_state() != 4)
		{		
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
				state = 41; //starting to enter room one.
				countLightR = 0;
			}
			FollowRightWall(NORMSPEED);	
		}		
		else
		{
			FollowRightWall(NORMSPEED);
		}	
	}
	else if (state == 41) //move straight til rear sensor crosses
	{
		if(lightRe > getLightRe())
		{		
			if(lightRe > getLightRe())
			{
				countLightRe++;
			}
			else
			{
				countLightRe = 0;
			}
			if( countLightRe > 10)  //countLightL > 10 ||
			{
				state = 42; //entered room one.
				countLightRe = 0;
				comingfrom++;
			}
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);	
		}		
		else
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
		}
	}
	else if (state == 42)
	{
		//look for fire, move in, rotate 630degrees CW
		resetDistances();
		while(getDistanceL() < 600)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);		//needs to move in further
		}	
		SetSpeed(0,0);
		SetTurnFire(NORMSPEED-200, 0, 60);			//IF FIRE: goto fire state
		frontLe = Adc_IR(IR_FR_L);
		frontLe = Adc_IR(IR_FR_L);
		LED1 = ~LED1;
		frontRi = Adc_IR(IR_FR_R);
		frontRi = Adc_IR(IR_FR_R);
		LED1 = ~LED1;
		if(state != 200)
		{
			SetTurn(NORMSPEED-200, 0, 260);
			while(frontLe > 17 && frontRi > 17)
			{
				SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
				frontLe = Adc_IR(IR_FR_L);
				frontLe = Adc_IR(IR_FR_L);
				LED1 = ~LED1;
				frontRi = Adc_IR(IR_FR_R);
				frontRi = Adc_IR(IR_FR_R);
				LED1 = ~LED1;
			}		
			state = 50;	
		}	
	}
	else if (state == 50)
	{
		if((lightF_R > getLightR()) && get_start_state() != 4)
		{		
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
				state = 51; //starting to exit room.
				countLightR = 0;
			}
			FollowRightWall(NORMSPEED);	
		}		
		else
		{
			FollowRightWall(NORMSPEED);
		}	
	}
	else if (state == 51)
	{
		if(lightRe > getLightRe())
		{		
			if(lightRe > getLightRe())
			{
				countLightRe++;
			}
			else
			{
				countLightRe = 0;
			}
			if( countLightRe > 10)  //countLightL > 10 ||
			{
				comingfrom++;
				if(comingfrom == 2)
				{
					state = 1; //leaving room one
				}
				else
				{
					state = 40;
				}	
				countLightRe = 0;
			}
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);	
		}		
		else
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
		}
	}
	else if (state == 100)
	{
		SetSpeed(0,0);
		setBlackLightCalibration();
		state = 40;
	}	
	else if (state == 200)		//FIRE CODE
	{
		if(lightF_R > getLightR())
		{		
			if(lightF_R > getLightR())
			{
				countLightR++;
			}
			else
			{
				countLightR = 0;
			}
			if( countLightR > 10)
			{
				state = 201; 
				countLightR = 0;
			}	
		}
		if(leftFr < 6)
		{
			SetSpeedDir(NORMSPEED-200, 0, NORMSPEED-200, 1);
		}
		else if(rightFr < 5)
		{
			SetSpeedDir(NORMSPEED-200, 1, NORMSPEED-200, 0);
		}		
		else if (fireL < 1000 && fireR < 1000)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
		}	
		else if(fireL < 1000)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED-600, 0);
		}	
		else if(fireR < 1000)
		{
			SetSpeedDir(NORMSPEED - 600, 0, NORMSPEED, 0);
		}
		else
		{
			SetSpeedDir(NORMSPEED-300, 0, NORMSPEED-300, 1);
		}	
			
	}
	else if (state == 201) //relay on while fire
	{
		if(fireL > 800 && fireR > 800)		// && fireM > 1500)
		{
			T4CONbits.TON = 0;
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 0);
		}
		else if(fireL < 801 && fireR < 801 && spray == 0)
		{
			SetSpeed(0, 0);
			T4CONbits.TON = 1;
			SetTurn(800, 1, 30);
			SetTurn(800, 0, 70);
			SetTurn(800, 1, 70);
			SetTurn(800, 0, 30);
			SetSpeed(0,0);
			spray = 1;	
		}
		else if(fireL < 801 && fireR < 801 && spray == 1)
		{
			SetSpeed(0, 0);
			T4CONbits.TON = 1;
			SetTurn(800, 0, 40);
			SetTurn(800, 1, 70);
			SetTurn(800, 0, 70);
			SetTurn(800, 1, 40);
			SetSpeed(0,0);
			spray = 0;
		}
		else if(fireL > 800)
		{
			T4CONbits.TON = 0;
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 0);
		}
		else if(fireR > 800)
		{
			T4CONbits.TON = 0;
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 1);
		}		
		else
		{
			LEDError = 1;
		}	
			
	}	
	else
	{
		LEDError = 1;
	}		
}

void setMainState(unsigned int stateGoto)
{
	state = stateGoto;
}
