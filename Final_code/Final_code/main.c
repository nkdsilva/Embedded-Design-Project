#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "keypad.h"

char password[1];
char lock[0];
char key;

void checkPassword();
void changePassword();
void getUserInput();
void goHome();

void initPorts(void);

int main(void)
{
	DDRA = 0xff;
	DDRC = 0xf0;
	initPorts();
	Lcd_init();
	
// 	eeprom_write_byte((uint8_t*)4,'6');
// 	eeprom_write_byte((uint8_t*)5,'5');
// 	eeprom_write_byte((uint8_t*)6,'4');
// 	eeprom_write_byte((uint8_t*)7,'5');
	
	LCD_String("WELCOME");
	_delay_ms(1000);
	goHome();
}

void goHome(void)
{
	Lcd_CmdWrite(0x01);
	LCD_String("OPEN DOOR-*");
	Lcd_CmdWrite(0xC0);
	LCD_String("CHANGE PIN-#");
	_delay_ms(1000);
			
	key=getKey();
	if(key=='*')
	{
		Lcd_CmdWrite(0x01);
		LCD_String("ENTER PIN");
		Lcd_CmdWrite(0xC0);
		_delay_ms(500);

		getUserInput();//GET PIN INPUT FROM USER
				
		_delay_ms(500);
		Lcd_CmdWrite(0x01);		
		LCD_String("CHECKING...");
		_delay_ms(500);
		Lcd_CmdWrite(0x01);

		checkPassword();//CHECK PASSWORD
				
	}
	else if(key='#')
	{
		//check the pin again
		Lcd_CmdWrite(0x01);
		LCD_String("ENTER PIN");
		Lcd_CmdWrite(0xC0);
		getUserInput();
		changePassword();
	}
}

void getUserInput(void)
{
	for(int i=0;i<4;i++)
	{
		key=getKey();
		_delay_ms(1000);
		//LCD_String("*");
		Lcd_DataWrite(key);//change later
		password[i]=key;
	}
}

void checkPassword(void)
{
	//CHECK THE PIN
	if ((eeprom_read_byte((uint8_t*)4)==password[0])&&(eeprom_read_byte((uint8_t*)5)==password[1])&&(eeprom_read_byte((uint8_t*)6)==password[2])&&(eeprom_read_byte((uint8_t*)7)==password[3]))
	{
		LCD_String("ACCESS GRANTED");
		_delay_ms(500);
		//to unlock the safe
		DDRD = 0xFF;//led-blue
		PORTD = 0B00000001;
		DDRH = 0xFF;//relay-high
		PORTH = 0x03;
		_delay_ms(1000);
		
		//to lock the safe
		Lcd_CmdWrite(0x01);
		LCD_String("Press #");
		Lcd_CmdWrite(0xC0);
		LCD_String("to lock");
		
		key=getKey();
		lock[0]=key;
		if(lock[0]=='#')
		{
			DDRD = 0xFF;//LED-red
			PORTD = 0B00000001;
			DDRH=0x00;//relay-low
			//PORTH=0B11110111;
			_delay_ms(3000);
			PORTH=0x00;//relay
			Lcd_CmdWrite(0x01);
			LCD_String("LOCKED");
		}
	}
	else if ((eeprom_read_byte((uint8_t*)4)!=password[0])||(eeprom_read_byte((uint8_t*)5)!=password[1])||(eeprom_read_byte((uint8_t*)6)!=password[2])||(eeprom_read_byte((uint8_t*)7)!=password[3]))
	{
		LCD_String("ACCESS DENIED!!!");
		DDRE |= 0xFF;
		PORTE |= 0B00000010;
				
		_delay_ms(1000);
		DDRD = 0xFF;//LED
		PORTD = 0x02;
	}
}

void changePassword(void)
{
	//CHECK THE PIN
	if ((eeprom_read_byte((uint8_t*)4)==password[0])&&(eeprom_read_byte((uint8_t*)5)==password[1])&&(eeprom_read_byte((uint8_t*)6)==password[2])&&(eeprom_read_byte((uint8_t*)7)==password[3]))
	{
		Lcd_CmdWrite(0x01);
		LCD_String("ENTER NEW PIN");
		Lcd_CmdWrite(0xC0);
		getUserInput();
		eeprom_write_byte((uint8_t*)4,password[0]);
		eeprom_write_byte((uint8_t*)5,password[1]);
		eeprom_write_byte((uint8_t*)6,password[2]);
		eeprom_write_byte((uint8_t*)7,password[3]);
		Lcd_CmdWrite(0x01);
		LCD_String("PASSWORD SAVED");
		_delay_ms(800);
		goHome();
	}
	else if ((eeprom_read_byte((uint8_t*)4)!=password[0])||(eeprom_read_byte((uint8_t*)5)!=password[1])||(eeprom_read_byte((uint8_t*)6)!=password[2])||(eeprom_read_byte((uint8_t*)7)!=password[3]))
	{
		Lcd_CmdWrite(0x01);
		LCD_String("TRY AGAIN");
		_delay_ms(800);
		goHome();
		DDRD = 0xFF;
		PORTD = 0x02;
	}
}

void initPorts(void)
{
	LcdDataBusDirnReg = 0xFF;
	DDRD &= 0B00000001;
}

