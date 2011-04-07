#include <p24HJ128GP210A.h>
#include "pins.h"
#include "init.h"
#include "timer.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"

//Config Bits set here
//Reference p24HJ128GP210A.h
_FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH & RBS_NO_RAM)
_FSS(SWRP_WRPROTECT_OFF & SSS_NO_FLASH & RSS_NO_RAM)
_FGS(GWRP_OFF & GCP_OFF & GSS_OFF)
//Oscillator config bits
_FOSCSEL(FNOSC_PRI & IESO_ON)
_FOSC(POSCMD_HS& OSCIOFNC_ON & FCKSM_CSECMD)

_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF & PLLKEN_OFF)
_FPOR(FPWRT_PWR128)
_FICD(ICS_PGD2 & JTAGEN_OFF)

char state = 0;

int main(void)
{
	unsigned int fireL = 0, fireR = 0, fireM = 0, lightF_L = 0, lightF_R = 0, lightR = 0;
	unsigned int countLightL = 0, countLightR = 0, countLightRe = 0;
	
	Pin_Init();
	Timer_Init();
	Adc_Init();
	PORTG = 0x0000;
	while(!go())
	{
		start();
	}
	
	//calibrate light here???
	
	while(1)
	{
//always read light sensors
		lightF_L = Adc_Read(LIGHT_L);
		lightF_R = Adc_Read(LIGHT_R);
		lightR = Adc_Read(LIGHT_RE);
		
//if in a room read fire sensors as well
		if(state == 1)
		{
			fireL = Adc_Read(FIRE_L);
			fireM = Adc_Read(FIRE_M);
			fireR = Adc_Read(FIRE_R);
		}
			
		if(state == 0)
		{
			if(lightF_L > getLightF_L() || lightF_R > getLightF_R())
			{
				if(lightF_L > getLightF_L())
				{
					countLightL++;
				}
				else
				{
					countLightL = 0;
				}		
				if(lightF_R > getLightF_R())
				{
					countLightR++;
				}
				else
				{
					countLightR = 0;
				}
			}		
			else
			{
				FollowRightWall(943);
			}	
		}
		else if (state == 1)
		{
			//look for fire, move in, rotate 630degrees CW
		}
		else
		{
			LEDError = 1;
		}		
	}	
}	
