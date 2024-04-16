#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

//ADMUX REFERENCE SELECTION BIT
#define ADMUX_REFS0        6
#define ADMUX_REFS1        7
#define ADMUX_ADLAR        5

//ADCSRA CONTROL AND STATUSE REGISTER
#define ADCSRA_ADEN        7
#define ADCSRA_ADSC        6
#define ADCSRA_ADATE       5
#define ADCSRA_ADIF        4
#define ADCSRA_ADIE        3
#define ADCSRA_ADPS2       2
#define ADCSRA_ADPS1       1
#define ADCSRA_ADPS0       0

//CHANNEL NUMBER
#define channel0           0b00000
#define channel1           0b00001
#define channel2           0b00010
#define channel3           0b00011
#define channel4           0b00100
#define channel5           0b00101
#define channel6           0b00110
#define channel7           0b00111

//prescaler
#define PRE_SCALER_VALUE   128

#endif
