#include "Lcd.h"
#include "Led.h"
#include "SN74LS595.h"
#include "Globle.h"
#include "Beep.h"//for test

extern float Mi[10]; 
extern unsigned int Tnum1;

unsigned char code sm_d[]={	//yin
0x3f,0x06,0x5b,0x4f,		//0 1 2 3
0x66,0x6d,0x7d,0x07,		//4 5 6 7
0x7f,0x6f,					//8 9 
0x6d,0x79,0x31				//SET(10,11,12)
};
				

void ShowWei(unsigned char wei)
{
	Wei10=0;
	switch(wei)
	{
		case 0: WeiD=1;WeiC=1;WeiB=1;WeiA=1;break;	//all close
		case 1:	WeiD=0;WeiC=0;WeiB=0;WeiA=1;break;	//1
		case 2:	WeiD=0;WeiC=0;WeiB=1;WeiA=0;break;	//2
		case 3:	WeiD=0;WeiC=1;WeiB=1;WeiA=0;break;	//3 
		case 4:	WeiD=1;WeiC=0;WeiB=0;WeiA=1;break;	 //4
		case 5:	WeiD=1;WeiC=0;WeiB=0;WeiA=0;break;	 //	5
		case 6:	WeiD=0;WeiC=1;WeiB=1;WeiA=1;break;	 //6
		case 7: Wei10=1;break;						//7
		case 8:	WeiD=0;WeiC=0;WeiB=1;WeiA=1;break;	 //8
		case 9:	WeiD=0;WeiC=1;WeiB=0;WeiA=0;break;	  //9
		case 10:WeiD=0;WeiC=1;WeiB=0;WeiA=1;break;	//10
		case 11:WeiD=0;WeiC=0;WeiB=0;WeiA=0;break;	  //11
		default:break;
	}

}
void ShowDataSingle(unsigned char banci,float num,unsigned char mode,unsigned char _flashWei)
{
	 unsigned char i;	
	 bit flash=0;		 //控制闪烁
	 long tmp	 ;
	 
	 int DateSt[6];

	

	 if(Tnum1>18)
	 {
	 	Tnum1=0;
	   	flash=~flash;
	 }
	 tmp= (long)(num*10);
   
	 //分离位数
	 DateSt[0]=tmp/100000;
	 DateSt[1]=tmp/10000%10;
	 DateSt[2]=tmp/1000%10;
	 DateSt[3]=tmp/100%10;
	 DateSt[4]=tmp/10%10;
	 DateSt[5]=tmp%10;

	ShowWei(0);
	LedMode(mode);
	 
	for(i=1;i<=7;i++)
	{
		if(i == _flashWei && i!=6)
		{
		 	ShowWei(i);
			if(flash)
				DataSend(sm_d[DateSt[i-2]]);
			DelayMs(1);
			DataSend(0);//消影
		
		}		 	
		else if(i == 1)
		{
			ShowWei(1);
			DataSend(sm_d[banci]);
			DelayMs(1);
			DataSend(0);
			ShowWei(0);

		 }
		 
		else if(i == 6)
		{
			 ShowWei(i);
			 if(_flashWei==6)
			 	;
			 else
			 	DataSend(sm_d[DateSt[i-2]] | 0x80);
			 DelayMs(1);
			 DataSend(0);//消影
			 ShowWei(0);

		}
		else
		{
			ShowWei(i);
			DataSend(sm_d[DateSt[i-2]]);
			DelayMs(1);
			DataSend(0);//消影
		}
	}	
}

void ShowData(unsigned char banci,float* Mi,unsigned char mode,unsigned char _flashWei)
{
	 unsigned char i;	//0xff 显示	 0不显示
	 bit flash=0;
		 
	 long int tmp = Mi[banci]*10;
	 int DateSt[6];

	 if(Tnum1>18)
	 {
	 	Tnum1=0;
	   	flash=~flash;
	 }
   
	 //分离位数
	 DateSt[0]=tmp/100000;
	 DateSt[1]=tmp/10000%10;
	 DateSt[2]=tmp/1000%10;
	 DateSt[3]=tmp/100%10;
	 DateSt[4]=tmp/10%10;
	 DateSt[5]=tmp%10;
	

	ShowWei(0);
	LedMode(mode);
	 
	for(i=1;i<=7;i++)
	{
		if(i == _flashWei && i!=6)
		{
		 	ShowWei(i);
			if(flash)
				DataSend(sm_d[DateSt[i-2]]);
			DelayMs(1);
			DataSend(0);//消影
		
		}		 	
		else if(i == 1)
		{
			ShowWei(1);
			DataSend(sm_d[banci]);
			DelayMs(1);
			DataSend(0);
			ShowWei(0);

		 }
		 
		else if(i == 6)
		{
			 ShowWei(i);
			 if(_flashWei==6)
			 	;
			 else
			 DataSend(sm_d[DateSt[i-2]] | 0x80);
			 DelayMs(1);
			 DataSend(0);//消影
			 ShowWei(0);

		}
		else
		{
			ShowWei(i);
			DataSend(sm_d[DateSt[i-2]]);
			DelayMs(1);
			DataSend(0);//消影
		}
	}	
}
void ShowKeyEv(bit _KeyEv)
{
	if(_KeyEv==0)		  //OFF
	{
			ShowWei(5);
			DataSend(sm_d[0]);
			DelayMs(1);
			DataSend(0);//消影

			ShowWei(6);
			DataSend(0x71);
			DelayMs(1);
			DataSend(0);//消影
				
			ShowWei(7);
			DataSend(0x71);
			DelayMs(1);
			DataSend(0);//消影	
	}
	else 		  //ON
	{
			ShowWei(6);
			DataSend(sm_d[0]);
			DelayMs(1);
			DataSend(0);//消影

			ShowWei(7);
			DataSend(0x37);
			DelayMs(1);
			DataSend(0);//消影	
	}

}  

void ShowSpeed(float speed)
{

     short i;
	 unsigned int _speed = (speed*10);
	 int DateSp[4];
	 DateSp[0]=_speed/1000;
 	 DateSp[1]=_speed/100%10;
 	 DateSp[2]=_speed/10%10;
	 DateSp[3]=_speed%10;

	for(i=8;i<=11;i++)
		{
			ShowWei(i);
			if(i==10)
		 		DataSend(sm_d[DateSp[i-8]]|0x80);
			else
				DataSend(sm_d[DateSp[i-8]]);
		 	DelayMs(1);
		 	DataSend(0);
		}


}
void ShowSet(unsigned char _i)
{
	unsigned char i;
	for(i=8;i<11;i++)
		{
			ShowWei(i);
		 	DataSend(sm_d[i+2]);
		 	DelayMs(1);
		 	DataSend(0);
		}
	ShowWei(i);
	DataSend(sm_d[_i]);
	DelayMs(1);
	DataSend(0);

}