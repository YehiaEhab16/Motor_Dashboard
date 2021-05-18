/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: KPD 				************/
/************		Version: 1.00	 		************/
/************		Date: 1-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8ColIdx, Local_u8RowIdx, Local_u8PressedKey=NO_PRESSED_KEY, Local_u8PinState;
	u8 Local_u8KPDArr[ROW_NUMBER][COLUMN_NUMBER] = KPD_BUTONS_VAL;
	u8 Local_u8ColumnArr[COLUMN_NUMBER] = {COLUMN_PIN0, COLUMN_PIN1, COLUMN_PIN2, COLUMN_PIN3};
	u8 Local_u8RowArr[ROW_NUMBER] = {ROW_PIN0, ROW_PIN1, ROW_PIN2, ROW_PIN3};

	for(Local_u8ColIdx=0;Local_u8ColIdx<COLUMN_NUMBER;Local_u8ColIdx++)
	{
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColIdx], DIO_u8PIN_LOW);

		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUMBER;Local_u8RowIdx++)
		{
			DIO_u8GetPinValue(KPD_PORT, Local_u8RowArr[Local_u8RowIdx], &Local_u8PinState);

			if(Local_u8PinState==DIO_u8PIN_LOW)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowIdx][Local_u8ColIdx];

				while(Local_u8PinState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_PORT, Local_u8RowArr[Local_u8RowIdx], &Local_u8PinState);
				}

				return Local_u8PressedKey;
			}
		}
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColIdx], DIO_u8PIN_HIGH);
	}


	return Local_u8PressedKey;
}
