#include <p24HJ128GP210A.h>
#include "pins.h"
#include "init.h"
#include "timer.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"
#include "statemachine.h"

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

unsigned int tempread = 0, tempread1 = 0, tempread2 = 0;
int main(void)
{	
	Pin_Init();
	Timer_Init();
	Adc_Init();
	calibrateSound();
	PORTG = 0x0000;
	//wait for start signal - sound for at elast 2 seconds or switch
	//***DEBUG********************
//	setMainState(1);
//	while(1)
//	{
//		stateOfMarvin();
//		tempread = Adc_IR(IR_FR_L);
//		tempread = Adc_IR(IR_FR_L);
//		LED1=~LED1;
//		tempread1 = Adc_IR(IR_FR_R);
//		tempread1 = Adc_IR(IR_FR_R);
//		LED1=~LED1;
//FollowRightWall(943);
//	}
	//*****************************
		
	while(!go())
	{
		start();
	}	
	//SetTurn(343, 0, 180);

	while(1)
	{
		stateOfMarvin();
//		tempread = Adc_Read(FIRE_L);
//		tempread = Adc_Read(FIRE_L);
//		LED1=~LED1;
//		tempread1 = Adc_Read(FIRE_M);
//		tempread1 = Adc_Read(FIRE_M);
//LED1=~LED1;
//		tempread2 = Adc_Read(FIRE_R);
//		tempread2 = Adc_Read(FIRE_R);
//LED1=~LED1;
	}		
}	
