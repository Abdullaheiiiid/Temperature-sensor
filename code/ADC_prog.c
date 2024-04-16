#include "bit.h"
#include "typedef.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include <util/delay.h>

//POINTERS TO CALL BACK FUNCTIONS
void (*ADC_CallBack)(void) = NULL;

void __vector_16(void) __attribute__((signal)); // ISR for INT0

void ADC_VidInit(void){

	//VCC REFERENCE VOLTAGE (AVCC with external capacitor at AREF pin)
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);

	//ACTIVE right ADJUST
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);

	//ADC CLOCK(PRESCALER)
	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS0);


	//ENABLE ADC
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}

void ADC_u16SOCAsyn(u8 Copy_u8Channel){

	//CLEAR THE MUX BITS
	ADMUX &= 0b11100000;

	//SET THE REQUIRED CHANNEL INTO THE MUX
	ADMUX |= Copy_u8Channel;

	//START CONVERSION
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	//ENABLE INTERRUPT
	SET_BIT(ADCSRA,ADCSRA_ADIE);

}

u16 ADC_ADCResult(){
	return ADCW;
}

//SET CALL BACK FUNCTION TO STORE FUNCTION IN PTR
void ADC_SetCallBack(void *Copy_PVidCallBack(void)){
	if(Copy_PVidCallBack != NULL){
		ADC_CallBack = Copy_PVidCallBack;
	}
}

// ISR for INT0
void __vector_16(void) {
	if(ADC_CallBack != NULL)
		ADC_CallBack();
}
