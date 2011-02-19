#include <p24HJ128GP210A.h>
#include "pins.h"
#include "init.h"
#include "timer.h"

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

#define On_Time  0xffff
#define Off_Time  0xffff
#define Pause_Time  0xffff


void main(void)
{
	
	int i=0;
	OSCCON=OSCCON | 0b0000000000000001;
	Pin_Init();
	Timer_Init();
	PORTG = 0xFFFF;
	while(1)
	{
		LED2=1;
		for(i=0; i<On_Time;i++) 
		{}
		LED2=0;
		for(i=0; i<On_Time;i++) 
		{}
	}	
}	
