/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: CLCD 				************/
/************		Version: 2.00	 		************/
/************		Date: 25-8-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	#if CLCD_CONFIGURATION == CLCD_BITS_8
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

	#elif CLCD_CONFIGURATION == CLCD_BITS_4
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB7, GET_BIT(Copy_u8Command,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB6, GET_BIT(Copy_u8Command,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB5, GET_BIT(Copy_u8Command,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB4, GET_BIT(Copy_u8Command,4));

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

	if(Copy_u8Command!=31)
	{
		DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB7, GET_BIT(Copy_u8Command,3));
		DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB6, GET_BIT(Copy_u8Command,2));
		DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB5, GET_BIT(Copy_u8Command,1));
		DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB4, GET_BIT(Copy_u8Command,0));

		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

	#endif
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	#if CLCD_CONFIGURATION == CLCD_BITS_8
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

	#elif CLCD_CONFIGURATION == CLCD_BITS_4

	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB7, GET_BIT(Copy_u8Data,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB6, GET_BIT(Copy_u8Data,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB5, GET_BIT(Copy_u8Data,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB4, GET_BIT(Copy_u8Data,4));

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB7, GET_BIT(Copy_u8Data,3));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB6, GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB5, GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_DB4, GET_BIT(Copy_u8Data,0));

	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

	#endif
}

void CLCD_voidInit(void)
{

	_delay_ms(40);

	#if CLCD_CONFIGURATION == CLCD_BITS_8
	CLCD_voidSendCommand(0b00111000);
	CLCD_voidSendCommand(0b00001100);
	CLCD_voidSendCommand(0b00000001);

	#elif CLCD_CONFIGURATION == CLCD_BITS_4
	CLCD_voidSendCommand(0b00100010);
	CLCD_voidSendCommand(0b10000000);
	CLCD_voidSendCommand(0b11000000);
	CLCD_voidSendCommand(0b00011111);

	#endif
}

void CLCD_voidSendString(const char* Copy_pchString)
{
	u8 Local_u8LoopIterator = 0, Local_u8XPos=0;
	while(Copy_pchString[Local_u8LoopIterator] != '\0')
	{
		CLCD_voidSendData(Copy_pchString[Local_u8LoopIterator]);
		Local_u8LoopIterator++;
		Local_u8XPos++;
		if(Local_u8XPos==16)
			CLCD_voidGotoXY(0, 1);
	}
}

void CLCD_voidSendNumber(u32 Copy_u32Number)
{
	u8 Local_u8Array[10],Local_u8LoopIterator = 0;
	if(Copy_u32Number==0)
		CLCD_voidSendData('0');
	else
	{
		while(Copy_u32Number != 0)
		{
			Local_u8Array[Local_u8LoopIterator] = Copy_u32Number%10;
			Copy_u32Number/=10;
			Local_u8LoopIterator++;
		}
		Local_u8LoopIterator--;
		while(Local_u8LoopIterator>0)
		{
			CLCD_voidSendData(Local_u8Array[Local_u8LoopIterator]+'0');
			Local_u8LoopIterator--;
		}
		CLCD_voidSendData(Local_u8Array[Local_u8LoopIterator]+'0');
	}
}

void CLCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8DDRAMAddress = Copy_u8XPos + 0x40*Copy_u8YPos;

	CLCD_voidSendCommand(Local_u8DDRAMAddress+128);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8YPatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress = Copy_u8YPatternNumber * 8,Local_u8Counter;

	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	CLCD_voidGotoXY(Copy_u8XPos, Copy_u8YPos);

	CLCD_voidSendData(Copy_u8YPatternNumber);
}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(1);
}
