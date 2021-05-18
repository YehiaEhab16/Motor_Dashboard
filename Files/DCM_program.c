/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: DCM			************/
/************		Version: 1.00	 		************/
/************		Date: 3-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DCM_config.h"
#include "DCM_interface.h"
#include "DCM_private.h"

void DCM_voidCCW(DCM_t* Copy_pu8StructMotor)
{
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinB, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinA, DIO_u8PIN_HIGH);
}
void DCM_voidCW(DCM_t* Copy_pu8StructMotor)
{
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinA, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinB, DIO_u8PIN_HIGH);
}
void DCM_voidStop(DCM_t* Copy_pu8StructMotor)
{
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinA, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_pu8StructMotor->DCM_u8Port, Copy_pu8StructMotor->DCM_u8PinB, DIO_u8PIN_LOW);
}
