
#include "LED_MAX7219.h"
#include "APP_FUNCTION.h"

/* LED 7-Segment MAX7219 */
void MAX7219_Init(void)
{
  unsigned short Data=0;

	/* intensity*/
	Data = 0x0A01;
	SPI1_Send16bit(&Data);
	
	/* scan limit*/
	Data = 0x0B07;
	SPI1_Send16bit(&Data);

	/* Normal Operation */
	Data = 0x0C01;
	SPI1_Send16bit(&Data);

	/* Display Test */
	/*SPI1_Send16bit(0x0F01);*/
 
	/* Decode mode */
	Data = 0x09FF;
	SPI1_Send16bit(&Data);

	/* set 1 for led 0 */
}

void LCD_Print(unsigned char Pos, unsigned char Number)
{
  unsigned short Data_Print;
  Data_Print = Number;
  Data_Print = (unsigned short)((Pos<<8) + (Data_Print));
	SPI1_Send16bit(&Data_Print);
}

void LCD_TurnOff(unsigned char Pos)
{
  unsigned short Data_Print;
  Data_Print = 0x0F;
  Data_Print |= (Pos<<8);
  SPI1_Send16bit(&Data_Print);
}

void LCD_TwoNumber(unsigned char Pos_1, unsigned char Pos_2, unsigned char Number)
{
  unsigned char So_DonVi;
  unsigned char So_Chuc;
	So_DonVi=0;
  So_Chuc=0;

  So_DonVi = (Number%10);
  So_Chuc = (Number/10);

  LCD_Print(Pos_1, So_DonVi);
  LCD_Print(Pos_2, So_Chuc);

}

void LCD_TimeDisplay(unsigned char Hour, unsigned char Minute, unsigned char Second)
{
  LCD_TurnOff(3);
  LCD_TurnOff(6);

  LCD_TwoNumber(1,2,Second);
  LCD_TwoNumber(4,5,Minute);
  LCD_TwoNumber(7,8,Hour);

}

void LCD_DayDisplay(unsigned char Day, unsigned char Month, unsigned char year)
{
  LCD_TurnOff(3);
  LCD_TurnOff(6);

  LCD_TwoNumber(1,2,year);
  LCD_TwoNumber(4,5,Month);
  LCD_TwoNumber(7,8,Day);

}

