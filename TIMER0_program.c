/*
 * TIMER0_program.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Abdelrahman
 */

#include <avr/interrupt.h>
#include "BIT_Math.h"
#include "TIMER0_interface.h"

static void (*TIMER0_Callback_Ptr)(void) = 0;
volatile u8 g_Timer0_OVF_initial_value = 0;
volatile u32 g_Timer0_OVF_target_ticks = 0;
volatile u32 g_Timer0_COMP_target_ticks = 0;

void TIMER0_Init(const TIMER0_Config_t *Config_Ptr)
{
	TCCR0 = (TCCR0 & 0xB7) | (Config_Ptr->mode);
	TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->compare_mode) << COM00);
	TIMSK = (TIMSK & 0xFC) | (Config_Ptr->interrupt_enable);
	sei();
}
void TIMER0_SetTimeMS(u32 time_ms, const TIMER0_Config_t *Config_Ptr)
{
	u32 prescaler_value;
	switch (Config_Ptr->prescaler)
	{
	case TIMER0_FCPU_1:
		prescaler_value = 1;
		break;
	case TIMER0_FCPU_8:
		prescaler_value = 8;
		break;
	case TIMER0_FCPU_64:
		prescaler_value = 64;
		break;
	case TIMER0_FCPU_256:
		prescaler_value = 256;
		break;
	case TIMER0_FCPU_1024:
		prescaler_value = 1024;
		break;
	}

	u32 total_ticks_required = (time_ms * (F_CPU / 1000.0)) / prescaler_value;
	if (Config_Ptr->mode == TIMER0_NORMAL_MODE)
	{
		g_Timer0_OVF_target_ticks = total_ticks_required / 256;

		g_Timer0_OVF_initial_value = 256 - (total_ticks_required % 256);

		TCNT0 = g_Timer0_OVF_initial_value;
	}
	else if (Config_Ptr->mode == TIMER0_CTC_MODE)
	{
		if (total_ticks_required <= 256)
		{
			OCR0 = (u8) (total_ticks_required - 1);
			g_Timer0_COMP_target_ticks = 1;
		}
		else
		{
			u32 num_compares = (u32) (total_ticks_required / 256);
			u8 remainder = total_ticks_required % 256;
			if (remainder == 0)
			{
				OCR0 = 255;
				g_Timer0_COMP_target_ticks = num_compares;
			}
			else
			{
				OCR0 = 256 - remainder;
				g_Timer0_COMP_target_ticks = num_compares + 1;

			}
		}

	}
}

void TIMER0_StartTimer(TIMER0_Config_t *Config_Ptr)
{
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);
}
void TIMER0_DeInit(void)
{
	TCNT0 = 0;
	TCCR0 = 0;
	OCR0 = 0;
	CLR_BIT(TIMSK, OCIE0);
	CLR_BIT(TIMSK, TOIE0);

	TIMER0_Callback_Ptr = 0;

}

void TIMER0_SetCallback(void (*callback)(void))
{
	TIMER0_Callback_Ptr = callback;
}

ISR(TIMER0_OVF_vect)
{
	static u32 Timer0_OVF_current_ticks = 0;

	Timer0_OVF_current_ticks++;

	if (Timer0_OVF_current_ticks >= g_Timer0_OVF_target_ticks)
	{
		Timer0_OVF_current_ticks = 0;
		if (TIMER0_Callback_Ptr != 0)
			TIMER0_Callback_Ptr();
	}
}

ISR(TIMER0_COMP_vect)
{
	static u32 Timer0_COMP_current_ticks = 0;
	Timer0_COMP_current_ticks++;
	OCR0 = 255;
	if (Timer0_COMP_current_ticks >= g_Timer0_COMP_target_ticks)
	{
		Timer0_COMP_current_ticks = 0;
		if (TIMER0_Callback_Ptr != 0)
			TIMER0_Callback_Ptr();
	}

}
