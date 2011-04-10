#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

char go_now = 0, start_state = 0;

void start()
{
	int temp = 0;
	unsigned int sound;
	sound = Adc_Read(SOUND);
	sound = Adc_Read(SOUND);
	
	if(sound > 2000 && start_state == 0)
	{
		PR6=0x9896;
		T6CONbits.TON = 1;
		start_state = 1;
	}
	if(STARTSWITCH && start_state == 0)
	{
		while(temp < 500)
		{
			if(!STARTSWITCH)
			{
				temp++;
			}
			else
			{
				temp = 0;
			}
		}
		start_state = 3;
	}
	if(start_state == 2)
	{
		while(sound > 2000){}
		start_state = 3;
	}
	if(start_state == 3)
	{
		go_now = 1;
		setWhiteLightCalibration();
		PR5 = 0x5C4B;
		PR6 = 0x9896;
		T6CONbits.TON = 1;
		start_state = 4;
	}	
	if(sound < 2000 && start_state == 1)
	{
		start_state = 0;
		T6CONbits.TON = 0;
	} 
}

char get_start_state()
{
	return start_state;
}

void set_start_state(char sss)
{
	start_state = sss;
}	
	
char go()
{
	return go_now;
}