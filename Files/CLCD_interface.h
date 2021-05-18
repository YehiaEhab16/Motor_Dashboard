/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: CLCD 				************/
/************		Version: 2.00	 		************/
/************		Date: 25-8-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendString(const char* Copy_pchString);

void CLCD_voidSendNumber(u32 Copy_u32Number);

void CLCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8YPatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos);

void CLCD_voidInit(void);

void CLCD_voidClearDisplay(void);


#endif
