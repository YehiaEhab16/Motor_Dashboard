/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: STP			************/
/************		Version: 1.00	 		************/
/************		Date: 14-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef STP_INTERFACE_H_
#define STP_INTERFACE_H_

#define STP_PORTA			DIO_u8PORTA
#define STP_PORTB			DIO_u8PORTB
#define STP_PORTC			DIO_u8PORTC
#define STP_PORTD			DIO_u8PORTD

#define STP_PIN0			DIO_u8PIN0
#define STP_PIN1			DIO_u8PIN1
#define STP_PIN2			DIO_u8PIN2
#define STP_PIN3			DIO_u8PIN3
#define STP_PIN4			DIO_u8PIN4
#define STP_PIN5			DIO_u8PIN5
#define STP_PIN6			DIO_u8PIN6
#define STP_PIN7			DIO_u8PIN7

typedef struct My_Struct5
{
	u8 STP_u8Port;
	u8 STP_u8PinBlue;
	u8 STP_u8PinPink;
	u8 STP_u8PinYellow;
	u8 STP_u8PinOrange;
}STP_t;

void STP_voidCCW(STP_t* Copy_pu8StructStepper, u16 Copy_u16Angle);
void STP_voidCW(STP_t* Copy_pu8StructStepper, u16 Copy_u16Angle);
void STP_voidStop(STP_t* Copy_pu8StructStepper);


#endif
