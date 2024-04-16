#include "bit.h"
#include "typedef.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>

int LOC=0;
//SEND COMMAN FUNCTION
void LCD_VidSendCommand( u8 Copy_u8Command){

	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_Low);

#if LCD_MODE == 8

	//SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Command);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#elif LCD_MODE == 4

	/* SEND 4 MSBs */
	u8 x = Copy_u8Command;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Copy_u8Command, 4));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Copy_u8Command, 5));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Copy_u8Command, 6));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Copy_u8Command, 7));

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

	                //--------------------------//

	/* SEND 4 LSBs */
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Copy_u8Command, 0));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Copy_u8Command, 1));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Copy_u8Command, 2));
	Copy_u8Command = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Copy_u8Command, 3));


	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#endif

}


//SEND DATA FUNCTION
void LCD_VidSendData( u8 Copy_u8Data){

#if LCD_MODE == 8


	//RS LOW  -->  SEND DATA
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_High);


	if(LOC == 16)
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION+LCD_SEGMENT_1_OF_ROW_1);
	else if(LOC == 32){
		_delay_ms(1000);
		LCD_VidSendCommand(LCD_CLEAR);
		LOC = -1;
	}
	LOC++;

	//SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Data);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#elif LCD_MODE == 4

	if(LOC == 16)
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION|LCD_SEGMENT_1_OF_ROW_1);
	else if(LOC == 32){
		_delay_ms(10000);
		LCD_VidSendCommand(LCD_CLEAR);
		LOC = -1;
	}
	LOC++;

	//RS LOW  -->  SEND DATA
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_High);

	/* SEND 4 MSBs */
	u8 x = Copy_u8Data;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Copy_u8Data, 4));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Copy_u8Data, 5));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Copy_u8Data, 6));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Copy_u8Data, 7));

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

	                //--------------------------//

	/* SEND 4 LSBs */
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Copy_u8Data, 0));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Copy_u8Data, 1));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Copy_u8Data, 2));
	Copy_u8Data = x;
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Copy_u8Data, 3));

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#endif

}


//INITIALIZATION FUNCTION
void LCD_VidInit(){

	//SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,Output);

	//SET PIN E DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,Output);

#if LCD_MODE == 8

	//SET PORT A DIRECTION TO BE OUTPUT
	DIO_VidSetPortDirection(LCD_DATA_PORT,Output);

	_delay_ms(40);

	//FUNCTION SET COMMAND: 8bit mode 2 LINES, 5*8 FONT SIZE
	LCD_VidSendCommand(LCD_EIGHT_BIT_MODE_TWO_LINES);

	//DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(LCD_CURSOR_OFF_BLINK);

	//CLEAR DISPLAY
	LCD_VidSendCommand(LCD_CLEAR);

#elif LCD_MODE == 4

	//SET MSBs OF PORT A DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN0, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN1, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN2, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN3, Output);

	_delay_ms(40);

	//FUNCTION SET COMMAND: 4bot mode
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_S1);
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_S2);

	//FUNCTION SET COMMAND: 4bit mode 2 LINES, 5*8 FONT SIZE
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_TWO_LINES);

	_delay_ms(40);
	//DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(LCD_CURSOR_OFF_BLINK);

	_delay_ms(40);
	//CLEAR DISPLAY
	LCD_VidSendCommand(LCD_CLEAR);

#endif
}

//SEND STRING FUNCTION
void LCD_VidSendString(char *Copy_u8Data){
	int Iterator = 0;
	while(Copy_u8Data[Iterator] != '\0'){
		LCD_VidSendData(Copy_u8Data[Iterator]);
		Iterator++;
	}
}

//SET POSITION FUNCTION
void LCD_VidSetPosition(u8 Copy_u8Row, u8 Copy_u8Columm){

	if(Copy_u8Row == LCD_ROW1){
		LOC = Copy_u8Columm;
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION|Copy_u8Columm);
	}
	else if(Copy_u8Row == LCD_ROW2){
		LOC = 16+Copy_u8Columm;
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION|LCD_SEGMENT_1_OF_ROW_1|Copy_u8Columm);
	}
}

//SEND NUMBER FUNCTION
void LCD_VidSendfloat(f32 Copy_u8Data){
	char floatStr[20];  // Adjust the size as needed
	int n = Copy_u8Data;
	int digit = 1;
	while(n!=0)
	   {
	       n=n/10;
	       digit++;
	   }
	dtostrf(Copy_u8Data, digit+2,2, floatStr);
	LCD_VidSendString(floatStr);
}

void LCD_VidSendint(int Copy_u8Data){
	char intstr[20];  // Adjust the size as needed
	sprintf(intstr,"%d",Copy_u8Data);
	LCD_VidSendString(intstr);
}

void LCD_VidClear()
{
	LOC =0;
	LCD_VidSendCommand(LCD_CLEAR);		/* Clear display */
	_delay_ms(2);
	LCD_VidSendCommand(LCD_FORCE_START_LOCATION);		/* Cursor at home position */
}


