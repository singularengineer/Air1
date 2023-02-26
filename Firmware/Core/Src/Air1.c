/*
 * Air1.c
 *
 *  Created on: Feb 14, 2023
 *      Author: SingularEngineer
 */

#include "Air1.h"
#include "stdlib.h"
#include <math.h>

//BAND
uint32_t M40_MIN = 7000000;
uint32_t M40_MAX = 7300000;

uint32_t encoder = 0;
int cursor_current = 0;
uint32_t freqency_current = 7150000;
uint32_t IncFactor = 1;
char lcd_buff[16];
char *lcd_ptr;

void Air1APP()
{
	HAL_GPIO_TogglePin(LED_HB_GPIO_Port, LED_HB_Pin);
	HAL_Delay(200);
	if(HAL_GPIO_ReadPin(ENC_SW_GPIO_Port, ENC_SW_Pin) ==  GPIO_PIN_RESET)
		UpdateCursor();
	else
		UpdateFreqency();

}

void UpdateCursor()
{
	LCD_Command(0x0E);
	int8_t cursor_update =  Encoder_Diff();
	int8_t cursor_temp = cursor_current + cursor_update;
	if((cursor_temp >= 0 ) && (cursor_temp < 7))
	{
		LCD_MoveCursor(0,cursor_temp);
		cursor_current = cursor_temp;
		IncFactor = pow(10,6 - cursor_current);
	}
}

void UpdateFreqency()
{
	//uint8_t len = 0;
	int16_t freq_diff = Encoder_Diff();
	uint32_t freq_temp = 0;

	if(freq_diff == 0)
		return;

	if(freq_diff > 0)
		freq_temp = freqency_current + IncFactor;
	if(freq_diff < 0)
		freq_temp = freqency_current - IncFactor;

	if((freq_temp <= M40_MAX) && (freq_temp >= M40_MIN))
	{
		LCD_MoveCursor(0,0);
		lcd_ptr = itoa(freq_temp,(char *)lcd_buff,10);
		SI5351_SetFrequency(CLK0, freq_temp);

		while(*lcd_ptr)
			LCD_Data(*lcd_ptr++);
		LCD_MoveCursor(0,cursor_current);
		freqency_current = freq_temp;
	}
}

int16_t Encoder_Diff()
{
	int16_t diff = 0;
	uint32_t encoder_new = TIM1->CNT>>2; // Divide by 2 as a filter

	if(encoder != encoder_new)
	{
		diff = encoder_new - encoder;
		encoder = encoder_new;
	}
	return diff;
}
