/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: KPD 				************/
/************		Version: 1.00	 		************/
/************		Date: 1-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


#define KPD_BUTONS_VAL		{{1,2,3,10},{4,5,6,11},{7,8,9,12},{13,0,14,15}}

#define NO_PRESSED_KEY		0xff  // number not in keypad numbers above

#define KPD_PORT			DIO_u8PORTC

#define COLUMN_PIN0			DIO_u8PIN4
#define COLUMN_PIN1			DIO_u8PIN5
#define COLUMN_PIN2			DIO_u8PIN6
#define COLUMN_PIN3			DIO_u8PIN7

#define ROW_PIN0			DIO_u8PIN3
#define ROW_PIN1			DIO_u8PIN2
#define ROW_PIN2			DIO_u8PIN1
#define ROW_PIN3			DIO_u8PIN0


#endif
