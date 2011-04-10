#include <p24HJ128GP210A.h>
#include "pins.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"
#include "timer.h"

unsigned int state = 0;
unsigned int countLightL = 0, countLightR = 0, countLightRe = 0;
const unsigned int NORMSPEED = 943;

void stateOfMarvin()
{
	unsigned int fireL = 0, fireR = 0, fireM = 0, lightF_R = 0, lightRe = 0;
	unsigned int frontLe = 0, frontRi = 0;
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
	}
		
	if(state == 0)
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
				state = 1; //starting to enter room one.
				countLightR = 0;
			}
			FollowRightWall(NORMSPEED);	
		}		
		else
		{
			FollowRightWall(NORMSPEED);
		}	
	}
	else if (state == 1) //move straight til rear sensor crosses
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
				state = 2; //entered room one.
				countLightRe = 0;
			}
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);	
		}		
		else
		{
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);
		}
	}
	else if (state == 2)
	{
		//look for fire, move in, rotate 630degrees CW
		resetDistances();
		while(getDistanceL() < 200)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);		//needs to move in further
		}	
		SetSpeed(0,0);
		SetTurnFire(NORMSPEED-200, 0, 630);			//IF FIRE: goto fire state
		frontLe = Adc_IR(IR_FR_L);
		frontLe = Adc_IR(IR_FR_L);
		LED1 = ~LED1;
		frontRi = Adc_IR(IR_FR_R);
		frontRi = Adc_IR(IR_FR_R);
		LED1 = ~LED1;
		while(frontLe > 14 && frontRi > 14)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
			frontLe = Adc_IR(IR_FR_L);
			frontLe = Adc_IR(IR_FR_L);
			LED1 = ~LED1;
			frontRi = Adc_IR(IR_FR_R);
			frontRi = Adc_IR(IR_FR_R);
			LED1 = ~LED1;
		}
		state = 3;	
	}	
	else if (state == 3) //looking for second room
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
			if( countLightR > 10)  //countLightL > 10 ||
			{
				state = 4; //starting to enter room two.
				countLightR = 0;
			}
			FollowRightWall(NORMSPEED);	
		}		
		else
		{
			FollowRightWall(NORMSPEED);
		}
	}
	else if (state == 4)
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
				state = 5; //entered room two.
				countLightRe = 0;
			}
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);	
		}		
		else
		{
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);
		}
	}
	else if (state == 5)
	{
		//look for fire, move in, rotate 630degrees CW
		resetDistances();
		while(getDistanceL() < 200)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);		//needs to move in further
		}	
		SetSpeed(0,0);
		SetTurnFire(NORMSPEED-200, 0, 630);			//IF FIRE: goto fire state
		frontLe = Adc_IR(IR_FR_L);
		frontLe = Adc_IR(IR_FR_L);
		LED1 = ~LED1;
		frontRi = Adc_IR(IR_FR_R);
		frontRi = Adc_IR(IR_FR_R);
		LED1 = ~LED1;
		while(frontLe > 14 && frontRi > 14)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
			frontLe = Adc_IR(IR_FR_L);
			frontLe = Adc_IR(IR_FR_L);
			LED1 = ~LED1;
			frontRi = Adc_IR(IR_FR_R);
			frontRi = Adc_IR(IR_FR_R);
			LED1 = ~LED1;
		}
		state = 6;	
	}
	else if (state == 6) //looking for room 3
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
			if( countLightR > 10)  //countLightL > 10 ||
			{
				state = 7; //starting to enter room three.
				countLightR = 0;
			}
			FollowRightWall(NORMSPEED);	
		}		
		else
		{
			FollowRightWall(NORMSPEED);
		}
	}
	else if (state == 7)	//move into room 3
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
				state = 8; //entered room three.
				countLightRe = 0;
			}
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);	
		}		
		else
		{
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 1);
		}
	}
	else if (state == 8) //look for fire in room 3
	{
		//look for fire, move in, rotate 630degrees CW
		resetDistances();
		while(getDistanceL() < 200)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);		//needs to move in further
		}	
		SetSpeed(0,0);
		SetTurnFire(NORMSPEED-200, 0, 630);			//IF FIRE: goto fire state
		frontLe = Adc_IR(IR_FR_L);
		frontLe = Adc_IR(IR_FR_L);
		LED1 = ~LED1;
		frontRi = Adc_IR(IR_FR_R);
		frontRi = Adc_IR(IR_FR_R);
		LED1 = ~LED1;
		while(frontLe > 14 && frontRi > 14)
		{
			SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
			frontLe = Adc_IR(IR_FR_L);
			frontLe = Adc_IR(IR_FR_L);
			LED1 = ~LED1;
			frontRi = Adc_IR(IR_FR_R);
			frontRi = Adc_IR(IR_FR_R);
			LED1 = ~LED1;
		}
		state = 9;
	}		
	else if(state == 9)
	{
		FollowRightWallMod(NORMSPEED);
	}	
	else if (state == 100)
	{
		SetSpeed(0,0);
		setBlackLightCalibration();
		state = 0;
	}	
	else if (state == 200)		//FIRE CODE
	{
		if(fireL < 1000 && fireR < 1000)
		{
			SetSpeed(0,0);
			state = 201;
		}	
		if(fireL < 1200)
		{
			SetSpeedDir(NORMSPEED, 1, NORMSPEED-200, 1);
		}	
		else if(fireR < 1200)
		{
			SetSpeedDir(NORMSPEED - 200, 1, NORMSPEED, 1);
		}
			
	}
	else if (state == 201) //relay on while fire
	{
		if(fireL > 1500 && fireR > 1500 && fireM > 1500)
		{
			T4CONbits.TON = 1;
			SetSpeedDir(NORMSPEED, 1, NORMSPEED, 0);
		}
		else
		{
			SetSpeed(0, 0);
			T4CONbits.TON = 1;
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
