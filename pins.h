#ifndef PINS_H
#define PINS_H

//defines pins as human readable names

//Format of code (* represents any name of pin)
//* gives a name to the specified pin so that * can be set or read in the program
//* Tris sets the Tris bit for the pin. 0 is output, 1 is input.

//Status LEDs
#define LED1 PORTDbits.RD11
#define LED1Tris TRISDbits.TRISD11
#define LED2 PORTDbits.RD10
#define LED2Tris TRISDbits.TRISD10
#define LED3 PORTBbits.RB6
#define LED3Tris TRISBbits.TRISB6
#define LED4 PORTBbits.RB7
#define LED4Tris TRISBbits.TRISB7

#define LEDStatus PORTGbits.RG15
#define LEDStatusTris TRISGbits.TRISG15
#define LEDError PORTDbits.RD4
#define LEDErrorTris TRISDbits.TRISD4

//Switches
#define STARTSWITCH PORTBbits.RB4
#define STARTSWITCH_Tris TRISBbits.TRISB4

//Relay
#define RELAY PORTBbits.RB5
#define RELAYTris TRISBbits.TRISB5

//Stepper
#define MS1_L PORTFbits.RF3
#define MS1_LTris TRISFbits.TRISF3
#define StepEn_L PORTFbits.RF7
#define StepEn_LTris TRISFbits.TRISF7
#define Dir_L PORTFbits.RF8
#define Dir_LTris TRISFbits.TRISF8
#define Step_L PORTFbits.RF2
#define Step_LTris TRISFbits.TRISF2

#define MS1_R PORTDbits.RD1
#define MS1_RTris TRISDbits.TRISD1
#define StepEn_R PORTDbits.RD12
#define StepEn_RTris TRISDbits.TRISD12
#define Dir_R PORTDbits.RD3
#define Dir_RTris TRISDbits.TRISD3
#define Step_R PORTDbits.RD2
#define Step_RTris TRISDbits.TRISD2

//Analog
//Gyro
#define GYRO_Z 	11
#define GYRO_ZTris TRISBbits.TRISB11

#define GyroSelfTest PORTFbits.RF6
#define GyroSelfTestTris TRISFbits.TRISF6
#define GyroSleep PORTGbits.RG3
#define GyroSleepTris TRISGbits.TRISG3
#define GyroHPReset PORTGbits.RG2
#define GyroHPResetTris TRISGbits.TRISG2

//Accelerometer
#define ACCEL_Z 26
#define ACCEL_Y 27
#define ACCEL_X 28
#define ACCEL_ZTris TRISEbits.TRISE2
#define ACCEL_YTris TRISEbits.TRISE3
#define ACCEL_XTris TRISEbits.TRISE4

#define AccelSlp PORTGbits.RG12
#define AccelSlpTris TRISGbits.TRISG12
#define AccelGS PORTGbits.RG13
#define AccelGSTris TRISGbits.TRISG13

//IR Sensors
#define IR_RI_F	29
#define IR_FR_R 30
#define IR_FR_L 20
#define IR_LE_F 21
#define IR_RE_L 14
#define IR_LE_R 15
#define IR_RE_R 23
#define IR_RI_R 24

#define IR_RI_F_Tris TRISEbits.TRISE5
#define IR_FR_R_Tris TRISEbits.TRISE6
#define IR_FR_L_Tris TRISAbits.TRISA12
#define IR_LE_F_Tris TRISAbits.TRISA13
#define IR_RE_L_Tris TRISBbits.TRISB14
#define IR_LE_R_Tris TRISBbits.TRISB15
#define IR_RE_R_Tris TRISAbits.TRISA7
#define IR_RI_R_Tris TRISEbits.TRISE1

//Fire Sensors
#define FIRE_R	31
#define FIRE_M 	17
#define FIRE_L 	19

#define FIRE_R_Tris TRISEbits.TRISE7
#define FIRE_M_Tris TRISCbits.TRISC2
#define FIRE_L_Tris TRISCbits.TRISC4

//Light
#define LIGHT_R 16
#define LIGHT_L 18
#define LIGHT_RE 22

#define LIGHT_R_Tris TRISCbits.TRISC1
#define LIGHT_L_Tris TRISCbits.TRISC3
#define LIGHT_RE_Tris TRISAbits.TRISA6

//Tone detect
#define SOUND 	25
#define SOUND_Tris TRISEbits.TRISE1

#endif
