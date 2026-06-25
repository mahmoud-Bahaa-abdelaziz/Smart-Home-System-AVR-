/*
 /*
 * EXTI_program.c
 *
 *  Created on: Aug 30, 2025
 *      Author: Abdelrahman
 */
#include <avr/interrupt.h>
#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO_intaeface.h"
#include "EXTI_interface.h"


static void (*INT0_CallBack)(void)=0;
static void (*INT1_CallBack)(void)=0;
static void (*INT2_CallBack)(void)=0;

void EXTI_Init(EXTI_Source_t source, EXTI_Trigger_t trigger)
{
	switch (source)
	{
	case EXTI_INT0:
		DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_INPUT);
		EXTI_Enable(EXTI_INT0);
		switch (trigger)
		{
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
			break;
		case EXTI_ANY_CHANGE:
			CLR_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
		case EXTI_FALLING_EDGE:
			SET_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
		}
		break;
	case EXTI_INT1:
		DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_INPUT);
		EXTI_Enable(EXTI_INT1);
		switch (trigger)
		{
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
			break;
		case EXTI_ANY_CHANGE:
			CLR_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
		case EXTI_FALLING_EDGE:
			SET_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
		}
		break;
	case EXTI_INT2:
		DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_INPUT);
		EXTI_Enable(EXTI_INT2);
		switch (trigger)
		{
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCSR, ISC2);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCSR, ISC2);
			break;
		}
		break;
	}
	SET_BIT(SREG, SREG_I);
}
void EXTI_Disable(EXTI_Source_t source)
{
	switch (source)
	{
	case EXTI_INT0:
		CLR_BIT(GICR, INT0);
		break;
	case EXTI_INT1:
		CLR_BIT(GICR, INT1);
		break;
	case EXTI_INT2:
		CLR_BIT(GICR, INT2);
		break;
	}
}

void EXTI_Enable(EXTI_Source_t source)
{
	switch (source)
	{
	case EXTI_INT0:
		SET_BIT(GICR, INT0);
		break;
	case EXTI_INT1:
		SET_BIT(GICR, INT1);
		break;
	case EXTI_INT2:
		SET_BIT(GICR, INT2);
		break;
	}

}
void EXTI_SetCallback(EXTI_Source_t source, void (*callback)(void))
{
	switch (source)
	{
	case EXTI_INT0:
		INT0_CallBack = callback;
		break;
	case EXTI_INT1:
		INT1_CallBack = callback;
		break;
	case EXTI_INT2:
		INT2_CallBack = callback;
		break;
	}
}
ISR(INT0_vect)
{
	if (INT0_CallBack != 0)
		INT0_CallBack();

}
ISR(INT1_vect)
{
	if (INT1_CallBack != 0)
		INT1_CallBack();
}

ISR(INT2_vect)
{
	if (INT2_CallBack != 0)
		INT2_CallBack();
}
