/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: SERVO			************/
/************		Version: 1.00	 		************/
/************		Date: 8-10-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

//brown->gnd , red->Vcc , orange->PWM

#define CHANNEL_A	1
#define CHANNEL_B	2

#define MINIMUM		700
#define MAXIMUM		3200

typedef struct My_Stuct123
{
	u8 Copy_u8Channel;
	u16 Copy_u16Angle;
}Servo_t;

//Channel A -> D5 , Channel B -> D4
void SERVO_voidInit(Servo_t* Copy_Servo_tData);	//angle from 0 to 180

void SERVO_voidRotate(Servo_t* Copy_Servo_tData);


#endif
