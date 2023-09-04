
#ifndef __LED_MAX7219__ 
#define __LED_MAX7219__

#include "STM32F1XX.h"

void MAX7219_Init(void);
void LCD_Print(unsigned char Pos, unsigned char Number);
void LCD_TurnOff(unsigned char Pos);
void LCD_TwoNumber(unsigned char Pos_1, unsigned char Pos_2, unsigned char Number);
void LCD_TimeDisplay(unsigned char Hour, unsigned char Minute, unsigned char Second);
void LCD_DayDisplay(unsigned char Day, unsigned char Month, unsigned char year);

#endif /* __LED_MAX7219__ */


