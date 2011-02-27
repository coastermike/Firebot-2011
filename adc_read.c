#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

void Adc_Init()
{
	AD1PCFGH = 0x0000;
	AD1PCFGL = 0xFFFC; //0x37EC; //0x37EF;
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
