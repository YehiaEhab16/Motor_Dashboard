/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: STP			************/
/************		Version: 1.00	 		************/
/************		Date: 14-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include <util/delay.h>

#include "DIO_interface.h"

#include "STP_config.h"
#include "STP_interface.h"
#include "STP_private.h"

void STP_voidCCW(STP_t* Copy_pu8StructStepper, u16 Copy_u16Angle)
{
	u16 Local_u16Counter, Local_u16Steps;

	while(Copy_u16Angle>360)
		Copy_u16Angle-=360;

	Local_u16Steps = (2048UL * (u32)Copy_u16Angle) / 360UL;

	for(Local_u16Counter=0;Local_u16Counter<Local_u16Steps/4;Local_u16Counter++)
	{
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_LOW);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);
	}
}
void STP_voidCW(STP_t* Copy_pu8StructStepper, u16 Copy_u16Angle)
{
	u16 Local_u16Counter, Local_u16Steps;

	while(Copy_u16Angle>360)
		Copy_u16Angle-=360;

	Local_u16Steps = (2048UL * (u32)Copy_u16Angle) / 360UL;

	for(Local_u16Counter=0;Local_u16Counter<Local_u16Steps/4;Local_u16Counter++)
	{
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_LOW);
		_delay_ms(2);
	}
}
void STP_voidStop(STP_t* Copy_pu8StructStepper)
{
	DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinBlue, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinPink, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinYellow, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_pu8StructStepper->STP_u8Port, Copy_pu8StructStepper->STP_u8PinOrange, DIO_u8PIN_HIGH);
}
