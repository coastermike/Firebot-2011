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

unsigned int accelz, accely, accelx, ir;

int main(void)
{
//	OSCCON=OSCCON | 0b0000000000000001;
	
	Pin_Init();
	Timer_Init();
	Adc_Init();
	StepperEnable();
	PORTG = 0x0000;
//	while(!go())
//	{
//		start();
//	}
	SetSpeed(5000, 5000);
	while(1)
	{
//		accelz = Adc_Read(ACCEL_Z);
//		accelx = Adc_Read(ACCEL_X);
//		accely = Adc_Read(ACCEL_Y);
		FollowRightWall(10000);
		accelx=Adc_IR(IR_FR_R);
	
			
	}	
}	
