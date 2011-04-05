#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

void Adc_Init()
{
	AD1PCFGH = 0x0000;
	AD1PCFGL = 0x37EF; //0x37EF;
	AD1CON1bits.AD12B = 1;
	AD1CON2bits.CHPS = 0b00;
	AD1CON2bits.VCFG = 0b000;
	AD1CON3bits.ADRC = 0;
	AD1CON3bits.ADCS = 0b00000001;
	AD1CON1bits.FORM = 0b00;
	AD1CON1bits.SSRC = 0b111;
	AD1CON3bits.SAMC = 0b00011;
	
	AD1CON1bits.ADON = 1;	
}

unsigned int Adc_Read(int ch)
{
	AD1CHS0bits.CH0SA = ch;
	AD1CON1bits.SAMP = 1;
	while(AD1CON1bits.DONE != 1)
	{}
	return ADC1BUF0;
}	

unsigned int Adc_IR(int ch)
{
	int k=0;
	unsigned int value = 0, raw = 0;
	int adc_table[NUMADC][2] = 
	{
		{2405, 4},
		{2073, 5},
		{1790, 6},
		{1540, 7},
		{1356, 8},
		{1267, 9},
		{1113, 10},
		{1000, 11},
		{913, 12},
		{808, 13},
		{779, 14},
		{739, 15},
		{717, 16},
		{686, 17},
		{635, 18},
		{623, 19},
		{592, 20},
		{576, 21}
	};
	
	raw = Adc_Read(ch);
	for(k=1; k < NUMADC; k++)
	{
		if(adc_table[k][0] < raw)	
		{
			value = adc_table[k-1][1] + (raw - adc_table[k-1][0]) *
				(adc_table[k][1] - adc_table[k-1][1]) / (adc_table[k][0] - adc_table[k-1][0]);
			break;
		}
	}	
	if (k == NUMADC)
	{
		value = adc_table[k-1][1];
	}
	if (value < 4)
	{
		value = 3;
	}
	else if(value > 30)
	{
		value = 30;
	}			
	return value;
}
