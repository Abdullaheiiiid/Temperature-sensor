#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

typedef enum{
	Channel0,
	Channel1,
	Channel2,
	Channel3,
	Channel4,
	Channel5,
	Channel6,
	Channel7
}ChannelName;

void ADC_VidInit(void);

void ADC_u16SOCAsyn(u8 Copy_u8Channel);

u16 ADC_ADCResult();

void ADC_SetCallBack(void *Copy_PVidCallBack(void));

#endif
