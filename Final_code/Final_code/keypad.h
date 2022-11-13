
#ifndef KEYPAD_H_
#define KEYPAD_H_



char keycheck()
{
	PORTC=0B01111111;
	//_delay_ms(10);
	if((PINC & 0B00001000)==0)//123A
	{
		return '1';
	}
	if((PINC & 0B00000100)==0)
	{
		return '2';
	}
	if((PINC & 0B00000010)==0)
	{
		return '3';
	}
	PORTC=0B10111111;//465B
	//_delay_ms(10);
	if((PINC & 0B00001000)==0)
	{
		return '4';
	}
	if((PINC & 0B00000100)==0)
	{
		return '5';
	}
	if((PINC & 0B00000010)==0)
	{
		return '6';
	}
	PORTC=0B11011111;//789C
	//_delay_ms(10);
	if((PINC & 0B00001000)==0)
	{
		return '7';
	}
	if((PINC & 0B00000100)==0)
	{
		return '8';
	}
	if((PINC & 0B00000010)==0)
	{
		return '9';
	}
	PORTC=0B11101111;//*0#D
	//_delay_ms(10);
	if((PINC & 0B00001000)==0)
	{
		return '*';
	}
	if((PINC & 0B00000100)==0)
	{
		return '0';
	}
	if((PINC & 0B00000010)==0)
	{
		return '#';
	}
	if((PINC & 0B00000001)==0)
	{
		return'D';
	}
	return 'a';
}

char getKey()
{
	char key='a';
	while(key=='a')
	{
		key=keycheck();
	}
	return key;
}

#endif /* KEYPAD_H_ */