#ifndef LCD_H_
#define LCD_H_

#define LcdDataBus    PORTA
#define LcdControlBus PORTA
#define LcdDataBusDirnReg DDRA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2



void Lcd_CmdWrite(char cmd)
{
	LcdDataBus = (cmd & 0xF0);
	LcdControlBus &= ~(1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);

	LcdDataBus = ((cmd<<4) & 0xF0);
	LcdControlBus &= ~(1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus = (dat & 0xF0);
	LcdControlBus |= (1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);

	LcdDataBus = ((dat<<4) & 0xF0);
	LcdControlBus |= (1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
}

void Lcd_init(void)
{
	Lcd_CmdWrite(0x02);
	Lcd_CmdWrite(0x28);
	Lcd_CmdWrite(0x0E);
	Lcd_CmdWrite(0x01);
	Lcd_CmdWrite(0x80);
}

void LCD_String (char *str) /* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++) /* Send each char of string till the NULL */
	{
		Lcd_DataWrite(str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	Lcd_CmdWrite((pos & 0x0F)|0x80); /* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	Lcd_CmdWrite((pos & 0x0F)|0xC0); /* Command of first row and required position<16 */
	LCD_String(str); /* Call LCD string function */
}


#endif /* LCD_H_ */