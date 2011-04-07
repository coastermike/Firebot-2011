#ifndef ADC_READ_H
#define ADC_READ_H

#define NUMADC 18
void Adc_Init();
unsigned int Adc_Read(int ch);
unsigned int Adc_IR(int ch);
void setLightCalibration(int left, int right, int rear);
unsigned int getLightF_L();
unsigned int getLightF_R();
unsigned int getLightR();

#endif
