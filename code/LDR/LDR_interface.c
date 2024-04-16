/*
 * LDR_interface.c
 *
 *  Created on: ١٠‏/٠٩‏/٢٠٢٣
 *      Author: abdul
 */

#include "../typedef.h"
#include "../ADC_interface.h"

u8 LDR_GetIntensityPercentage() {
	u16 value =  ADC_ADCResult();
	u8 percentage = 100-(((float)value / 1023)*100);
	return percentage;
}
