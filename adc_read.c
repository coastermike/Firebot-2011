#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

unsigned int lightL_W, lightR_W, lightRe_W, lightL_B, lightR_B, lightRe_B, lightR, lightL, lightRe;

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
	
void Adc_Init()
{	
	AD1PCFGH = 0x0000;
	AD1PCFGL = 0x37FF; //0x37FF;
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

unsigned int calibrateLightL()
{
	int i;
	unsigned int light_total = 0, tempLight;
	for(i=0; i < 10; i++)
	{
		tempLight = Adc_Read(LIGHT_L);
		tempLight = Adc_Read(LIGHT_L);
		light_total = tempLight + light_total;
	}
	return light_total/10;
}

unsigned int calibrateLightR()
{
	int i;
	unsigned int light_total = 0, tempLight;
	for(i=0; i < 10; i++)
	{
		tempLight = Adc_Read(LIGHT_R);
		tempLight = Adc_Read(LIGHT_R);
		light_total = tempLight + light_total;
	}
	return light_total/10;
}

unsigned int calibrateLightRe()
{
	int i;
	unsigned int light_total = 0, tempLight;
	for(i=0; i < 10; i++)
	{
		tempLight = Adc_Read(LIGHT_RE);
		tempLight = Adc_Read(LIGHT_RE);
		light_total = tempLight + light_total;
	}
	return light_total/10;
}
	
void setWhiteLightCalibration()//white is higher
{
	lightL_W = calibrateLightL();
	lightR_W = calibrateLightR();
	lightRe_W = calibrateLightRe();
	lightL = lightL_W - 500;
	lightR = lightR_W - 500;
	lightRe = lightRe_W - 500;
}

void setBlackLightCalibration()//Black is lower
{
	lightL_B = calibrateLightL();
	lightR_B = calibrateLightR();
	lightRe_B = calibrateLightRe();
	lightL = (lightL_W + lightL_B)/2;
	lightR = (lightR_W + lightR_B)/2;
	lightRe = (lightRe_W + lightRe_B)/2;	
}
	
unsigned int getLightL()
{
	return lightL;
}
	
unsigned int getLightR()
{
	return lightR;
}
	
unsigned int getLightRe()
{
	return lightRe;
}
