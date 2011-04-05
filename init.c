#include "pins.h"
#include <p24HJ128GP210A.h>

//Sets the Tris bits of the pins that are not part of a peripheral
void Pin_Init()
{
	//setting all Tris bits
	LED1Tris = 0;
	LED2Tris = 0;
	LED3Tris = 0;
	LED4Tris = 0;
	LEDStatusTris = 0;
	LEDErrorTris = 0;
	
	RELAYTris = 0;
	
	//steppers
	MS1_LTris = 0;
	StepEn_LTris = 0;
	Dir_LTris = 0;
	Step_LTris = 0;
	
	MS1_RTris = 0;
	StepEn_RTris = 0;
	Dir_RTris = 0;
	Step_RTris = 0;
	
	//analog pins
	GYRO_ZTris = 1;
	GyroSelfTestTris = 0;
	GyroSleepTris = 0;
	GyroHPResetTris = 0;
	
	ACCEL_ZTris = 1;
	ACCEL_YTris = 1;
	ACCEL_XTris = 1;
	AccelSlpTris = 0;
	AccelGSTris = 0;
	AccelGS = 0;
	
	IR_RI_F_Tris = 1;
	IR_FR_R_Tris = 1;
	IR_FR_L_Tris = 1;
	IR_LE_F_Tris = 1;
	IR_RE_L_Tris = 1;
	IR_LE_R_Tris = 1;
	IR_RE_R_Tris = 1;
	IR_RI_R_Tris = 1;
	
	FIRE_R_Tris = 1;
	FIRE_L_Tris = 1;
	FIRE_M_Tris = 1;
	
	LIGHT_R_Tris = 1;
	LIGHT_L_Tris = 1;
	LIGHT_RE_Tris = 1;
	
	STARTSWITCH_Tris = 1;
}
