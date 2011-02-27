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
#define MS1 PORTFbits.RF0
#define MS1Tris TRISFbits.TRISF0
#define StepEN PORTFbits.RF1
#define ENTris TRISFbits.TRISF1
#define StepDIR PORTGbits.RG0
#define DIRTris TRISGbits.TRISG0
#define Step PORTGbits.RG1
#define StepTris TRISGbits.TRISG1

//Analog
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

//Gyro


//Accelerometer


//IR Sensors
#define IR1 TRISBbits.TRISB0
#define IR2 TRISBbits.TRISB1

//Fire Sensors


//Tone detect


//Battery


#endif
