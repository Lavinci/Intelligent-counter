#include "Globle.h"

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


void DelayUs(uint t)
{
	for(t;t>0;t--)
		Delay1us();
}
void DelayMs(uint t)
{
	for(t;t>0;t--)
		Delay1ms();
}