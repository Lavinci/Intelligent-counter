#include "LED.h"
#include "Globle.h"
#include "SN74LS595.h"



void LedMode(unchar mode)  //1 Ϊ���,2Ϊ ��,3Ϊ��
{
	ledI = 1; 
	if(mode == 1)	DataSend(0x80);
	if(mode == 2)	DataSend(0x40);
	if(mode == 2)	DataSend(0x20);
}