#include "Lcd.h"
#include "SN74LS595.h"
#include "Globle.h"


unsigned char code sm_d[]={	//yin
0x3f,0x06,0x5b,0x4f,		//0 1 2 3
0x66,0x6d,0x7d,0x07,		//4 5 6 7
0x7f,0x6f,0x77,0x7c,		//8 9 A b
0x39,0x5e,0x79,0x71,		//C d E F
0x80};


void ShowWei(unchar wei)
{
	wei10=0;
	switch(wei)
	{
		case 0: WeiD=0;WeiC=0;WeiB=0;WeiA=0;break;	//wei0
		case 1:	WeiD=0;WeiC=0;WeiB=0;WeiA=1;break;
		case 2:	WeiD=0;WeiC=0;WeiB=1;WeiA=0;break;
		case 3:	WeiD=0;WeiC=0;WeiB=1;WeiA=1;break;
		case 4:	WeiD=0;WeiC=1;WeiB=0;WeiA=0;break;
		case 5:	WeiD=0;WeiC=1;WeiB=0;WeiA=1;break;
		case 6:	WeiD=0;WeiC=1;WeiB=1;WeiA=0;break;
		case 7:	WeiD=0;WeiC=1;WeiB=1;WeiA=1;break;
		case 8:	WeiD=1;WeiC=0;WeiB=0;WeiA=0;break;
		case 9:	WeiD=1;WeiC=0;WeiB=0;WeiA=1;break;
		case 10:WeiD=1;WeiC=1;WeiB=1;WeiA=1;wei10=1;break;	
		default:break;
	}

}

/*
void ShowData(unchar dat)
{
	DataSend(dat);
}
	高级功能扩展
*/
void Test()
{
	unchar i=0;
	for(i;i<11;i++)
	{		
		DataSend(0);	//消影
		ShowWei(i);
		DataSend(sm_d[i]);
		if(i==10) i=0;
	}
}