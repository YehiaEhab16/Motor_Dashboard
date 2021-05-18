/*
 * main.c
 *
 *  Created on: Sep 14, 2020
 *      Author: yehia
 */

#include "STD_TYPES.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMERS_interface.h"

#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "STP_interface.h"
#include "SERVO_interface.h"

u16 combine(u16 Copy_u8First,u16 Copy_u8Second);

void main(void)
{
	u8 Local_u8HamokshaWalk1[8] = { 0b00000100, 0b00001010, 0b00000100, 0b00010100, 0b00001110, 0b00000101, 0b00000110, 0b00001010 };
	u8 Local_u8HamokshaWalk2[8] = { 0b00000100, 0b00001010, 0b00000100, 0b00000101, 0b00001110, 0b00010100, 0b00000110, 0b00000101 };
	u8 Local_u8Clear[8]= { 0, 0, 0, 0, 0, 0, 0, 0 }, Local_u8LoopCounter, Local_u8Iterator=0;
	u8 Local_u8Switch, Local_u8Activate;
	u16 Local_u16Angle, Local_u16Potentiometer, Local_u16LM35, Local_u16Temperature;

	PORT_voidInit();
	ADC_voidInit();

	CLCD_voidInit();

	STP_t Local_su8Stepper = {STP_PORTA, STP_PIN2, STP_PIN3, STP_PIN4, STP_PIN5};

	Servo_t Local_Servo_tMotor = {CHANNEL_B, 0};

	PWM_t Local_PWM_tMotorPinA = {TIMER0, 0};
	PWM_t Local_PWM_tMotorPinB = {TIMER2, 0};

	PWM_voidInit(&Local_PWM_tMotorPinA);
	PWM_voidInit(&Local_PWM_tMotorPinB);

	SERVO_voidInit(&Local_Servo_tMotor);

	for(Local_u8LoopCounter=0;Local_u8LoopCounter<15;Local_u8LoopCounter++)
	{
		CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk1, 0, Local_u8LoopCounter, 0);
		_delay_ms(300);
		Local_u8LoopCounter++;
		CLCD_voidWriteSpecialCharacter(Local_u8Clear, 2, Local_u8Iterator, 0);
		Local_u8Iterator++;
		CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk2, 1, Local_u8LoopCounter, 0);
		_delay_ms(300);
		CLCD_voidWriteSpecialCharacter(Local_u8Clear, 2, Local_u8Iterator, 0);
		Local_u8Iterator++;
	}
	Local_u8Iterator=15;
	CLCD_voidGotoXY(0,0);
	CLCD_voidSendString("Welcome to MotorDash-board App");
	_delay_ms(2000);
	CLCD_voidClearDisplay();

	while(1)
	{
		Local_u8Activate=4;
		Local_u16Angle = 0;
		CLCD_voidGotoXY(0,0);
		CLCD_voidSendString("DCM:1    STP:2  Servo:3  Exit:4");

		Local_u8Switch = KPD_u8GetPressedKey();

		if(Local_u8Switch == 1)
		{
			CLCD_voidClearDisplay();
			while(1)
			{
				CLCD_voidGotoXY(0,0);
				CLCD_voidSendString("CW:1            CCW:2");

				Local_u8Switch = KPD_u8GetPressedKey();

				if(Local_u8Switch==1 || Local_u8Switch==2)
				{
					Local_u8Activate = Local_u8Switch;
					CLCD_voidClearDisplay();
				}

				while(Local_u8Activate==1)
				{
					CLCD_voidGotoXY(0,0);
					CLCD_voidSendString("Full Speed:1    Pot:2  Temp:3");
					Local_u8Switch = KPD_u8GetPressedKey();
					if(Local_u8Switch==1)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Enter any key   to exit");

							Local_PWM_tMotorPinA.PWM_Value=255;
							Local_PWM_tMotorPinB.PWM_Value=0;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinA.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
								break;
							}
						}
					}

					else if(Local_u8Switch==2)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							ADC_u8StartConversionSynch(0, &Local_u16Potentiometer);

							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Motor Speed:");
							CLCD_voidSendNumber(Local_u16Potentiometer);

							Local_PWM_tMotorPinA.PWM_Value=Local_u16Potentiometer;
							Local_PWM_tMotorPinB.PWM_Value=0;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinA.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
								break;
							}
						}
					}

					else if(Local_u8Switch==3)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							ADC_u8StartConversionSynch(1, &Local_u16LM35);
							Local_u16Temperature = ((u32)Local_u16LM35 * 5000UL) / 256UL;
							Local_u16Temperature/=10;

							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Temperature:");
							CLCD_voidSendNumber(Local_u16Temperature);

							if(Local_u16Temperature>39)
								Local_PWM_tMotorPinA.PWM_Value=255;
							else if(Local_u16Temperature>37)
								Local_PWM_tMotorPinA.PWM_Value=230;
							else if(Local_u16Temperature>35)
								Local_PWM_tMotorPinA.PWM_Value=215;
							else if(Local_u16Temperature>33)
								Local_PWM_tMotorPinA.PWM_Value=200;
							else if(Local_u16Temperature>31)
								Local_PWM_tMotorPinA.PWM_Value=185;
							else
								Local_PWM_tMotorPinA.PWM_Value=0;

							Local_PWM_tMotorPinB.PWM_Value=0;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinA.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
								break;
							}
						}
					}

				}

				while(Local_u8Activate==2)
				{
					CLCD_voidGotoXY(0,0);
					CLCD_voidSendString("Full Speed:1    Pot:2  Temp:3");
					Local_u8Switch = KPD_u8GetPressedKey();
					if(Local_u8Switch==1)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Enter any key   to exit");

							Local_PWM_tMotorPinA.PWM_Value=0;
							Local_PWM_tMotorPinB.PWM_Value=255;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinB.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);
								break;
							}
						}
					}

					else if(Local_u8Switch==2)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							ADC_u8StartConversionSynch(0, &Local_u16Potentiometer);

							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Motor Speed:");
							CLCD_voidSendNumber(Local_u16Potentiometer);

							Local_PWM_tMotorPinA.PWM_Value=0;
							Local_PWM_tMotorPinB.PWM_Value=Local_u16Potentiometer;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinB.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);
								break;
							}
						}
					}

					else if(Local_u8Switch==3)
					{
						CLCD_voidClearDisplay();
						while(1)
						{
							ADC_u8StartConversionSynch(1, &Local_u16LM35);
							Local_u16Temperature = ((u32)Local_u16LM35 * 5000UL) / 256UL;
							Local_u16Temperature/=10;

							CLCD_voidGotoXY(0,0);
							CLCD_voidSendString("Temperature:");
							CLCD_voidSendNumber(Local_u16Temperature);

							if(Local_u16Temperature>39)
								Local_PWM_tMotorPinB.PWM_Value=255;
							else if(Local_u16Temperature>37)
								Local_PWM_tMotorPinB.PWM_Value=230;
							else if(Local_u16Temperature>35)
								Local_PWM_tMotorPinB.PWM_Value=215;
							else if(Local_u16Temperature>33)
								Local_PWM_tMotorPinB.PWM_Value=200;
							else if(Local_u16Temperature>31)
								Local_PWM_tMotorPinB.PWM_Value=185;
							else
								Local_PWM_tMotorPinB.PWM_Value=0;

							Local_PWM_tMotorPinA.PWM_Value=0;

							PWM_voidAnalogWrite(&Local_PWM_tMotorPinA);
							PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);

							Local_u8Switch = KPD_u8GetPressedKey();
							if(Local_u8Switch>=1 && Local_u8Switch<=15)
							{
								CLCD_voidClearDisplay();
								Local_u8Activate = 3;
								Local_PWM_tMotorPinB.PWM_Value=0;
								PWM_voidAnalogWrite(&Local_PWM_tMotorPinB);
								break;
							}
						}
					}

				}

				if(Local_u8Activate==3)
					break;
			}
		}

		else if(Local_u8Switch == 2)
		{
			CLCD_voidClearDisplay();
			while(1)
			{
				CLCD_voidGotoXY(0,0);
				CLCD_voidSendString("CW:1            CCW:2");

				Local_u8Switch = KPD_u8GetPressedKey();
				if(Local_u8Switch==1 || Local_u8Switch==2)
				{
					Local_u8Activate = Local_u8Switch;
					CLCD_voidClearDisplay();
				}

				while(Local_u8Activate==1)
				{
					CLCD_voidGotoXY(0,0);
					CLCD_voidSendString("Enter the       angle:");

					Local_u8Switch = KPD_u8GetPressedKey();
					if(Local_u8Switch>=0 && Local_u8Switch<=9)
						Local_u16Angle = combine(Local_u16Angle, Local_u8Switch);
					else if(Local_u8Switch==15)
					{
						while(Local_u16Angle>360)
							Local_u16Angle-=360;
						CLCD_voidClearDisplay();
						CLCD_voidSendString("Rotating with   angle:");
						CLCD_voidSendNumber(Local_u16Angle);
						STP_voidCW(&Local_su8Stepper, Local_u16Angle);
						Local_u8Activate=3;
						CLCD_voidClearDisplay();
						break;
					}
					CLCD_voidSendNumber(Local_u16Angle);
				}

				while(Local_u8Activate==2)
				{
					CLCD_voidGotoXY(0,0);
					CLCD_voidSendString("Enter the       angle:");

					Local_u8Switch = KPD_u8GetPressedKey();
					if(Local_u8Switch>=0 && Local_u8Switch<=9)
						Local_u16Angle = combine(Local_u16Angle, Local_u8Switch);
					else if(Local_u8Switch==15)
					{
						while(Local_u16Angle>360)
							Local_u16Angle-=360;
						CLCD_voidClearDisplay();
						CLCD_voidSendString("Rotating with   angle: ");
						CLCD_voidSendNumber(Local_u16Angle);
						STP_voidCCW(&Local_su8Stepper, Local_u16Angle);
						Local_u8Activate=3;
						CLCD_voidClearDisplay();
						break;
					}
					CLCD_voidSendNumber(Local_u16Angle);
				}

				if(Local_u8Activate==3)
					break;
			}
		}

		else if(Local_u8Switch == 3)
		{
			CLCD_voidClearDisplay();
			while(1)
			{
				CLCD_voidGotoXY(0,0);
				CLCD_voidSendString("Enter the       angle:");

				Local_u8Switch = KPD_u8GetPressedKey();
				if(Local_u8Switch>=0 && Local_u8Switch<=9)
					Local_u16Angle = combine(Local_u16Angle, Local_u8Switch);
				else if(Local_u8Switch==15)
				{
					while(Local_u16Angle>360)
						Local_u16Angle-=360;
					CLCD_voidClearDisplay();
					CLCD_voidSendString("Rotating with   angle: ");
					CLCD_voidSendNumber(Local_u16Angle);
					Local_Servo_tMotor.Copy_u16Angle=Local_u16Angle;
					SERVO_voidRotate(&Local_Servo_tMotor);
					_delay_ms(1000);
					CLCD_voidClearDisplay();
					break;
				}
				CLCD_voidSendNumber(Local_u16Angle);
			}
		}

		else if(Local_u8Switch == 4)
		{
			CLCD_voidClearDisplay();
			for(Local_u8LoopCounter=15;Local_u8LoopCounter>1;Local_u8LoopCounter--)
			{
				CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk1, 0, Local_u8LoopCounter, 0);
				_delay_ms(300);
				Local_u8LoopCounter--;
				CLCD_voidWriteSpecialCharacter(Local_u8Clear, 2, Local_u8Iterator, 0);
				Local_u8Iterator--;
				CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk2, 1, Local_u8LoopCounter, 0);
				_delay_ms(300);
				CLCD_voidWriteSpecialCharacter(Local_u8Clear, 2, Local_u8Iterator, 0);
				Local_u8Iterator--;
			}
			CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk1, 0, 1, 0);
			_delay_ms(300);
			CLCD_voidWriteSpecialCharacter(Local_u8Clear, 2, 1, 0);
			CLCD_voidWriteSpecialCharacter(Local_u8HamokshaWalk2, 1, 0, 0);
			_delay_ms(300);
			CLCD_voidClearDisplay();
			while(1)
			{
				CLCD_voidGotoXY(2,0);
				CLCD_voidSendString("Thank You :)");
			}
		}
	}
}

u16 combine(u16 Copy_u8First, u16 Copy_u8Second)
{
    u8 times=1;

    if(Copy_u8Second == 0)
    	return Copy_u8First*10;

    while(times<=Copy_u8Second)
        times *= 10;

    return Copy_u8First * times + Copy_u8Second;
}
