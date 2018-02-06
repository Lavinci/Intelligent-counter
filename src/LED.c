#include "LED.h"
#include "Globle.h"
#include "SN74LS595.h"



void LedMode(unsigned char mode)  //1 为输出,2为 米,3为码
{

	LedI = 1; 
	if(mode == 1)	DataSend(0x20);
	if(mode == 2)	DataSend(0x40);
	if(mode == 3)	DataSend(0x80);
	DelayMs(1);
	LedI = 0;
}