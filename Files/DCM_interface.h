/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: DCM			************/
/************		Version: 1.00	 		************/
/************		Date: 3-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

#define DCM_PORTA			DIO_u8PORTA
#define DCM_PORTB			DIO_u8PORTB
#define DCM_PORTC			DIO_u8PORTC
#define DCM_PORTD			DIO_u8PORTD

#define DCM_PIN0			DIO_u8PIN0
#define DCM_PIN1			DIO_u8PIN1
#define DCM_PIN2			DIO_u8PIN2
#define DCM_PIN3			DIO_u8PIN3
#define DCM_PIN4			DIO_u8PIN4
#define DCM_PIN5			DIO_u8PIN5
#define DCM_PIN6			DIO_u8PIN6
#define DCM_PIN7			DIO_u8PIN7

typedef struct My_Struct4
{
	u8 DCM_u8Port;
	u8 DCM_u8PinA;
	u8 DCM_u8PinB;
}DCM_t;

void DCM_voidCCW(DCM_t* Copy_pu8StructMotor);
void DCM_voidCW(DCM_t* Copy_pu8StructMotor);
void DCM_voidStop(DCM_t* Copy_pu8StructMotor);


#endif
