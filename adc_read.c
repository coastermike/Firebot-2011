#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

#define irsensor1 0
#define irsensor2 1
#define IR_RI_F	29
#define IR_FR_R 30
#define FIRE_R	31
#define LIGHT_R 16
#define FIRE_M 	17
#define LIGHT_L 18
#define FIRE_L 	19
#define IR_FR_L 20
#define IR_LE_F 21
#define SPARE 	4
#define GYRO_Z 	11
#define IR_RE_L 14
#define IR_LE_R 15
#define LIGHT_RE 22
#define IR_RE_R 23
#define IR_RI_R 24
#define SOUND 	25
#define ACCEL_Z 26
#define ACCEL_Y 27
#define ACCEL_X 28

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
