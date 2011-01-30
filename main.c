#include <p24HJ128GP210A.h>
#include "pins.h"
#include "init.h"

void main(void)
{
	int i=0;
	Pin_Init();
	while(1)
	{
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;
//		for(i=0;i<1000;i++);
//		LED1=0;
//		for(i=0;i<1000;i++);
	}	
}	
