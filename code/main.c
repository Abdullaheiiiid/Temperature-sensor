/*
 * main.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٣
 *      Author: abdul
 */

#include "typedef.h"
#include "bit.h"
#include "DIO_Private.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "LDR/LDR_interface.h"
#include <util/delay.h>

void ADC_LM35_FUNCTION(void);
void ADC_LDR_FUNCTION(void);
void ADC_PIR_FUNCTION(void);
void ADC_FLAME_FUNCTION(void);
int main()
{
	ADC_VidInit();
	LCD_VidInit();
	GIE_VidEnable();

	while(1){
		ADC_u16SOCAsyn(Channel0);
		ADC_SetCallBack(&ADC_LDR_FUNCTION);
	}
	return 0;
}

void ADC_LM35_FUNCTION(void) {
	u16 r;
	int cel;
	r =  ADC_ADCResult();
	//STEP == 5/1024 = 0.00488
	//ANALOG = DIGITAL * STEP *1000 --> mV
	cel = (r*4.88);
	cel=(cel/10.00);
	_delay_ms(50);
	LCD_VidSendString("Temprature : ");
	LCD_VidSendint(cel);
	LCD_VidSendString(" C");
	_delay_ms(400);
	LCD_VidClear();
}

void ADC_LDR_FUNCTION(void) {
	u8 percentage = LDR_GetIntensityPercentage();
	_delay_ms(50);
	LCD_VidSendString("Light : ");
	LCD_VidSendint(percentage);
	LCD_VidSendString(" %");
	_delay_ms(400);
	LCD_VidClear();
}

void ADC_PIR_FUNCTION(void) {
	u16 pirValue = ADC_ADCResult();

	u16 threshold = 512;

	if (pirValue > threshold) {
		DIO_VidSetPinValue(Port_C, Pin0, Pin_High);

	} else {
		DIO_VidSetPinValue(Port_C, Pin0, Pin_Low);
	}
	u8 percentage = (pirValue / 1023) * 100;
	_delay_ms(50);
	LCD_VidSendString("digital : ");
	LCD_VidSendint(percentage);
	LCD_VidSendString(" %");
	_delay_ms(400);
	LCD_VidClear();
}
void ADC_FLAME_FUNCTION(void) {
	u16 flameValue = ADC_ADCResult();

	if (flameValue != 0 ) {
		DIO_VidSetPinValue(Port_C, Pin1, Pin_High);

	} else {
		DIO_VidSetPinValue(Port_C, Pin1, Pin_Low);
	}
	_delay_ms(100);
}
