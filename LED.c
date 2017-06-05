#include "LED.h"
#include "Globle.h"
#include "SN74LS595.h"



void LedMode(unchar mode)  //1 为输出,2为 米,3为码
{
	ledI = 1; 
	if(mode == 1)	DataSend(0x80);
	if(mode == 2)	DataSend(0x40);
	if(mode == 2)	DataSend(0x20);
}