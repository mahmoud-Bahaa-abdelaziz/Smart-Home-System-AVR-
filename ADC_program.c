/*
 * ADC_program.c
 *
 *  Created on: Aug 31, 2025
 *      Author: Abdelrahman
 */
#include "BIT_Math.h"
#include "ADC_interface.h"
#include "avr/interrupt.h"

volatile u16 g_adcResult = 0;

ISR(ADC_vect)
{
	g_adcResult = ADC;
}

void ADC_Init(const ADC_Config_t *Config_Ptr)
{
	ADMUX = 0;
	ADCSRA = 0;

	ADMUX = (ADMUX & 0xE0) | (Config_Ptr->channel);
	ADMUX = (ADMUX & 0xDF) | ((Config_Ptr->adlar) << ADLAR);
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt) << REFS0);

	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);
	ADCSRA = (ADCSRA & 0xF7) | ((Config_Ptr->interrupt) << ADIE);

	SET_BIT(ADCSRA, ADEN);

}
u16 ADC_ReadChannel_Polling(u8 channel_num)
{
	ADMUX = (ADMUX & 0xE0) | (channel_num);
	SET_BIT(ADCSRA, ADSC);
	while (GET_BIT(ADCSRA, ADIF) == 0)
		;
	SET_BIT(ADCSRA, ADIF);
	return ADC;
}
void ADC_ReadChannel_Interrupt(u8 channel_num)
{
	sei();
	ADMUX = (ADMUX & 0xE0) | (channel_num);
	SET_BIT(ADCSRA, ADSC);
}

