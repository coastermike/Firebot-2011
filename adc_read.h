#ifndef ADC_READ_H
#define ADC_READ_H

#define NUMADC 27
void Adc_Init();
unsigned int Adc_Read(int ch);
unsigned int Adc_IR(int ch);
void setWhiteLightCalibration();
void setBlackLightCalibration();
unsigned int getLightL();
unsigned int getLightR();
unsigned int getLightRe();

#endif
