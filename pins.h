#ifndef PINS_H
#define PINS_H

//defines pins as human readable names

//Format of code (* represents any name of pin)
//* gives a name to the specified pin so that * can be set or read in the program
//* Tris sets the Tris bit for the pin. 0 is output, 1 is input.

//Status LEDs
//RG12, RG13, RG14, RG15
#define LED1 PORTGbits.RG12
#define LED1Tris TRISGbits.TRISG12
#define LED2 PORTGbits.RG13
#define LED2Tris TRISGbits.TRISG13
#define LED3 PORTGbits.RG14
#define LED3Tris TRISGbits.TRISG14
#define LED4 PORTGbits.RG15
#define LED4Tris TRISGbits.TRISG15

//Switches


//Stepper


//Analog
//Gyro


//Accelerometer


//IR Sensors


//Fire Sensors


//Tone detect


//Battery


#endif
