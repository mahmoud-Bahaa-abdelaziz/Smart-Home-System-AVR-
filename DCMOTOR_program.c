/*
 * DCMOTOR_program.c
 *
 *  Created on: Aug 28, 2025
 *      Author: Abdelrahman
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include"DIO_intaeface.h"
#include "DCMOTOR_interface.h"
#include "DCMOTOR_config.h"
#include "Lm35_interface.h"
void DCMOTOR_Init(void)
{
	DIO_SetPinDirection(DCMOTOR_PORT, DCMOTOR_PIN1, DIO_OUTPUT);
	DIO_SetPinDirection(DCMOTOR_PORT, DCMOTOR_PIN2, DIO_OUTPUT);
	DCMOTOR_Stop();
}
void DCMOTOR_Forward(void)
{
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN1, DIO_HIGH);
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN2, DIO_LOW);
}
void DCMOTOR_Backward(void)
{
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN1, DIO_LOW);
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN2, DIO_HIGH);
}
void DCMOTOR_Stop(void)
{
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN1, DIO_LOW);
	DIO_SetPinValue(DCMOTOR_PORT, DCMOTOR_PIN2, DIO_LOW);
}
void DCMOTOR_TempControl(void)
{
    u8 temp = Lm35_ReadTemperature();  // Read temperature

    if(temp > 20)
    {
        DCMOTOR_Forward();   // Move motor forward if temp > 20
    }
    else
    {
        DCMOTOR_Stop();      // Stop motor if temp <= 20
    }
}
