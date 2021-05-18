/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: SERVO			************/
/************		Version: 1.00	 		************/
/************		Date: 8-10-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "TIMERS_interface.h"

#include "SERVO_config.h"
#include "SERVO_interface.h"
#include "SERVO_private.h"

void SERVO_voidInit(Servo_t* Copy_Servo_tData)
{
	u16 Local_u16ServoAngle = mapping(Copy_Servo_tData->Copy_u16Angle, 0, 180, MINIMUM, MAXIMUM);

	Timer_t Local_Timer_tServo = {FAST_PWM, DIVIDE_BY_8, Local_u16ServoAngle, NON_INVERTED, Copy_Servo_tData->Copy_u8Channel, 25000};
	Timer1_voidInit(&Local_Timer_tServo);

}

void SERVO_voidRotate(Servo_t* Copy_Servo_tData)
{
	u16 Local_u16ServoAngle = mapping(Copy_Servo_tData->Copy_u16Angle, 0, 180, MINIMUM, MAXIMUM);

	if(Copy_Servo_tData->Copy_u8Channel==CHANNEL_B)
		Timer_voidSetTimerValue(TIMER1_COMPARE_MATCH_B, Local_u16ServoAngle);
	else
		Timer_voidSetTimerValue(TIMER1_COMPARE_MATCH_A, Local_u16ServoAngle);
}
