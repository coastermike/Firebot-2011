#ifndef ADC_READ_H
#define ADC_READ_H

#define NUMADC 18
void Adc_Init();
unsigned int Adc_Read(int ch);
unsigned int Adc_IR(int ch);

#endif
