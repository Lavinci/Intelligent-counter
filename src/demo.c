#include "Globle.h"
#include "KeyScan.h"
#include "Led.h"
#include "Lcd.h"
#include "Beep.h"
#include "STC15.h"
#include "SN74LS595.h"
#include "Date.h"
#include "string.h"


float Mi[10];   //保存九个班次的米数
unsigned char banci;	//班次
float speed;		//速度
float Total;	//总长

float Xishu;
float DelayTime;
bit KeyEv;	//键盘开启状态
unsigned char  mode;//0 mi,1ma
unsigned int Tnum=0;	//定时器0,用于键盘扫描  
unsigned int Tnum1=0;	//定时器0,用于lcd闪烁
unsigned int banciTmp=0;	//用于轮换显示
unsigned int time1s=0;

unsigned char revDat[7]={0x55,0xAA,0x02,0x00,0x00};		//窜口收数据比对
unsigned char buff[7];									//串口数据缓存
sbit CodeA=P1^0;
sbit CodeB=P1^1;

enum {
	eShow,
	eRun_Count=101,eRun_Length,
	eSet_Length,eSet_Xishu,eSet_Delay,eSet_Key
	}state;

void Init();   
void UartInit(void)	;
int Ischarcmp();
void eepromm();
int poww(int y)
{
	int i,x=1;
	for(i=0;i<y;i++)
		x*=10;
	return x;
}

void main()
{  
   	unsigned char tmp;	 //接收键值
 	unsigned char i;	 //临时循环使用
	unsigned char flashWei=2;	  //用于控制设置闪烁位

	Init();
	DelayMs(200);    //	  上电延时200MS，等电源稳定后再运行程序
	if(state==eRun_Count)
	Beep(1);		 //响铃启动成功

while(1)
{
	WDT_CONTR=0x35;	   //看门狗
	eepromm();
	switch(state)
	{
		case eShow:	
			if(banci>9)
			{
				state=eRun_Count;
				banci=0;
				Beep(1);
			}
			if(banciTmp>20)
			{
				banciTmp=0;
				banci++;
			}

			ShowData(banci,Mi,mode,0);
			
			break;
	
		case eRun_Count:
		{	
			if(tmp=KeyScan())
			{
	
				switch(tmp)
				{
					case 11:	flashWei=2;state=eSet_Length;break;			//要求是码制不能设定
					case 12:	state=eShow;banci=0;break;						//累计态
					case 3:	
						Beep(1);											   
						if(mode==2)	
						{	
									
							mode=3;
							miToma();
							break;
						}
									
						if(mode==3)
						{
							mode=2;
							maTomi();//maTomi
							break;
						}
						
					case 4:		//中断实现清零,先用软件模拟
					{					
						for(i=0;i<10;i++)
							Mi[i]=0;
							break;
					}		
					case 5:
					{
						if(banci==9) banci=0;
						else banci++;
						break;
					}
				}	 
			}
				ShowData(banci,Mi,mode,0);
				ShowSpeed(speed);
				break;
			}
/*-----------------------------------------------------*/
			case eRun_Length:
			{	
			if(tmp=KeyScan())
			{
	
				switch(tmp)
				{
					case 11:	flashWei=2;state=eSet_Length;break;			//要求是码制不能设定
					case 12:	state=eShow;break;						//累计态
					case 3:		
						Beep(1);										   
						if(mode==2)	
						{	
									
							mode=3;
							//miToma
							break;
						}
										
						if(mode==3)
						{
							mode=2;
							//maTomi
							break;
						}
						
					case 4:		//中断实现清零,先用软件模拟
					{					
						for(i=0;i<10;i++)
							Mi[i]=0;
							break;
					}		
					case 5:
					{
						if(banci==9) banci=0;
						else banci++;
						break;
					}
				}	 
			}
				ShowData(banci,Mi,mode,0);
				ShowSpeed(speed);
				break;
			}
/*-----------------------------------------------------*/
			case eSet_Length:
				if(tmp=KeyScan())
				switch(tmp)
				{
					case 1: flashWei=2;state=eSet_Xishu;break;
					case 2:	
					{	
						if(flashWei==7) 
							flashWei=2; 
						else 
							flashWei++;
						break;
					 }
					case 3:	 	
						if(flashWei==2)
							Mi[banci]+=10000;
						else
							Mi[banci]+= (float)((0.1000)*poww(7-flashWei));
						if(Mi[banci]>99999)
							Mi[banci]=0;
						break;
					default:break;
				}
				ShowData(banci,Mi,mode,flashWei);
				ShowSet(1);
				break;
/*-----------------------------------------------------*/
			case eSet_Xishu:	
				if(tmp=KeyScan())
				switch(tmp)
				{
					case 1: flashWei=2;state=eSet_Delay;break;
					case 2:	
					{	
						if(flashWei==7) 
							flashWei=2; 
						else 
							flashWei++;
						break;
					 }
					case 3:	 	
						if(flashWei==2)
							Xishu+=10000;
						else
							Xishu+= (float)((0.1)*poww(7-flashWei));
						if(Xishu>99999)
							Xishu=0;
						break;
					default:break;
				}
				ShowDataSingle(banci,Xishu,mode,flashWei);
				ShowSet(2);
				break;

/*-----------------------------------------------------*/
			case eSet_Delay:
				if(tmp=KeyScan())
				switch(tmp)
				{
					case 1: flashWei=2;state=eSet_Key;break;
					case 2:	
					{	
						if(flashWei==7) 
							flashWei=2; 
						else 
							flashWei++;
						break;
					 }
					case 3:	 	
						if(flashWei==2)
							DelayTime+=10000;
						else
							DelayTime+= (float)((0.1)*poww(7-flashWei));
						if(Xishu>99999)
							DelayTime=0;
						break;
					default:break;
				}
				ShowDataSingle(banci,DelayTime,mode,flashWei);
				ShowSet(3);
				break;
/*-----------------------------------------------------*/
			case eSet_Key:
			if(tmp=KeyScan())
				switch(tmp)
				{
					case 1: flashWei=2;state=eRun_Count;break;
					case 2:	break;
					case 3:	 	
						KeyEv=~KeyEv;
						break;
					default:break;
				}
				ShowKeyEv(KeyEv);
				ShowSet(4);
				break;
/*-----------------------------------------------------*/
			default: break;
		}

	}

}



void Init()
{
	unsigned char i;

	AUXR &= 0;		//定时器时钟12T模式
	TMOD = 0x11;
	EA=1;		 		//开总中断
	ET0=1;				//开定时器0中断
	ET1=1;	
	TR0=1;		   //开定时器0
	UartInit();		   //初始化串口


	state=eRun_Count;	//初始为运行态
//   	state=eShow;//for test

	ShowWei(0);		//关闭全部口
	mode=2;			//默认米模式

	for(i=0;i<10;i++)
	  	Mi[i]=(float)byte_read(0x2000+i*8) / 10;
	banci=byte_read(0x2200);			//默认班次
	speed=(float)byte_read(0x2216) /10;	
	Xishu=(float)byte_read(0x2232) /10;
	DelayTime=(float)byte_read(0x2248) /10;	  
	KeyEv=(bit)(float)byte_read(0x2264);
}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x70;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	ES=1;
	TR1 = 1;		//启动定时器1
}

void Timer0Init(void)	interrupt 1	//50毫秒@11.0592MHz	   定时器零中断,用来计算按键时间和控制设置显示
{

	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	Tnum++;
	Tnum1++;
	banciTmp++;
	time1s++;
	if(	CodeB == 0 )
		Mi[banci]+=Xishu;

}

	
int Ischarcmp()			 //用来比较接收到的数据
{
	int i;

	for(i=0;i<5;i++)
	if(revDat[i]!=buff[i])
		return 0;

	return 1;
}   


void rev() interrupt 4
{
	static char i=0;
 	unsigned char revData;

	static tmplast=0;
	float speedtmp;

	RI=0;
	revData=SBUF;
	/**********************模拟编码器****************/

	if(revData == 1)
		Mi[banci]+=1;

   	if(time1s >=20)
	{
		speed=Mi[banci]-tmplast;
		tmplast=Mi[banci];
		time1s=0;
	}

	/*
	if(i==5)		 //接收5次数据则进行一次比较
	{
		if(Ischarcmp())							//如果启动字符正确,发送数据并重置次数
		{
			DateOut(revData);
	   	 	i=0;
			memset(buff,0,sizeof(buff));
			return;
		}
		else									//如果不正确,重置次数
		{
			i=0;
			memset(buff,0,sizeof(buff));
			return;
		}

	}											 //处理收到的数据
		buff[i++]=revData;
		*/

}

void eepromm()
{
	int i;
	for(i=0;i<10;i++)
	  	byte_write((0x2000+i*8),(unsigned char)(Mi[i]*10));
	byte_write(0x2200,banci);
	byte_write(0x2216,(unsigned char)(speed*10));
	byte_write(0x2232,(unsigned char)(Xishu*10));
	byte_write(0x2248,(unsigned char)(DelayTime*10));
	byte_write(0x2264,(unsigned char)(KeyEv));  

}






