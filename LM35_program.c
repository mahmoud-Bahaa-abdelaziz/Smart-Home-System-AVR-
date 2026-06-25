/*
 * LM35_program.c
 *
 *  Created on: Sep 1, 2025
 *      Author: Abdelrahman
 */
#include "Lm35_interface.h"

u8 Lm35_ReadTemperature(void)
{
	u8 temperature = 0;
	u16 adc_reading = ADC_ReadChannel_Polling(LM35_ADC_CHANNEL);

	temperature = ((u32)adc_reading * ADC_REF_VOLT_VALUE * 1000) / (ADC_MAXIMUM_VALUE * 10);
	return temperature;
}
