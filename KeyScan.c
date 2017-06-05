#include "KeyScan.h"
#include "Beep.h"
#include "SN74LS595.h"

unsigned char KeyScan()
{
   unsigned char KNum=0;


	KEY=1;	  //没按高电平

	DataSend(0xF8);
	if(KEY != 1)
	{
		Delay1ms();
		if(KEY != 1)
		{
			
			DataSend(0x78);				
			if(KEY != 1) KNum=1;
			DataSend(0xB8);
			if(KEY != 1) KNum=2;
			DataSend(0xD8);
			if(KEY != 1) KNum=3;	
			DataSend(0xE8);
			if(KEY != 1) KNum=4;	
			DataSend(0xF8);
			if(KEY != 1) KNum=5;		
		}
		while(KEY != 1)
		{
		 Delay1ms();
		}		
	} 

	switch(KNum)	  //预留按键事件
	{
	
		default: Beep(1);break;
	
	}

	return KNum;
}