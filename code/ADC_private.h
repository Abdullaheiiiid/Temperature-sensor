#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

//ADMUX REFERANCE SELECTION BIT
#define ADMUX      *((volatile u8*)0x27)

//ADCSRA CONTROL AND STATUS REGISTER
#define ADCSRA     *((volatile u8*)0x26)

//READ CONVERTION VALUE
#define ADCW     *((volatile u16*)0x24)

#endif
