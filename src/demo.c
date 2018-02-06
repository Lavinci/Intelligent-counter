#include "Globle.h"
#include "KeyScan.h"
#include "Led.h"
#include "Lcd.h"
#include "Beep.h"
#include "STC15.h"
#include "SN74LS595.h"
#include "Date.h"
#include "string.h"


float Mi[10];   //����Ÿ���ε�����
unsigned char banci;	//���
float speed;		//�ٶ�
float Total;	//�ܳ�

float Xishu;
float DelayTime;
bit KeyEv;	//���̿���״̬
unsigned char  mode;//0 mi,1ma
unsigned int Tnum=0;	//��ʱ��0,���ڼ���ɨ��  
unsigned int Tnum1=0;	//��ʱ��0,����lcd��˸
unsigned int banciTmp=0;	//�����ֻ���ʾ
unsigned int time1s=0;

unsigned char revDat[7]={0x55,0xAA,0x02,0x00,0x00};		//�ܿ������ݱȶ�
unsigned char buff[7];									//�������ݻ���
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
   	unsigned char tmp;	 //���ռ�ֵ
 	unsigned char i;	 //��ʱѭ��ʹ��
	unsigned char flashWei=2;	  //���ڿ���������˸λ

	Init();
	DelayMs(200);    //	  �ϵ���ʱ200MS���ȵ�Դ�ȶ��������г���
	if(state==eRun_Count)
	Beep(1);		 //���������ɹ�

while(1)
{
	WDT_CONTR=0x35;	   //���Ź�
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
					case 11:	flashWei=2;state=eSet_Length;break;			//Ҫ�������Ʋ����趨
					case 12:	state=eShow;banci=0;break;						//�ۼ�̬
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
						
					case 4:		//�ж�ʵ������,�������ģ��
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
					case 11:	flashWei=2;state=eSet_Length;break;			//Ҫ�������Ʋ����趨
					case 12:	state=eShow;break;						//�ۼ�̬
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
						
					case 4:		//�ж�ʵ������,�������ģ��
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

	AUXR &= 0;		//��ʱ��ʱ��12Tģʽ
	TMOD = 0x11;
	EA=1;		 		//�����ж�
	ET0=1;				//����ʱ��0�ж�
	ET1=1;	
	TR0=1;		   //����ʱ��0
	UartInit();		   //��ʼ������


	state=eRun_Count;	//��ʼΪ����̬
//   	state=eShow;//for test

	ShowWei(0);		//�ر�ȫ����
	mode=2;			//Ĭ����ģʽ

	for(i=0;i<10;i++)
	  	Mi[i]=(float)byte_read(0x2000+i*8) / 10;
	banci=byte_read(0x2200);			//Ĭ�ϰ��
	speed=(float)byte_read(0x2216) /10;	
	Xishu=(float)byte_read(0x2232) /10;
	DelayTime=(float)byte_read(0x2248) /10;	  
	KeyEv=(bit)(float)byte_read(0x2264);
}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0x70;		//�趨��ʱ��ֵ
	TH1 = 0xFF;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	ES=1;
	TR1 = 1;		//������ʱ��1
}

void Timer0Init(void)	interrupt 1	//50����@11.0592MHz	   ��ʱ�����ж�,�������㰴��ʱ��Ϳ���������ʾ
{

	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x4C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	Tnum++;
	Tnum1++;
	banciTmp++;
	time1s++;
	if(	CodeB == 0 )
		Mi[banci]+=Xishu;

}

	
int Ischarcmp()			 //�����ȽϽ��յ�������
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
	/**********************ģ�������****************/

	if(revData == 1)
		Mi[banci]+=1;

   	if(time1s >=20)
	{
		speed=Mi[banci]-tmplast;
		tmplast=Mi[banci];
		time1s=0;
	}

	/*
	if(i==5)		 //����5�����������һ�αȽ�
	{
		if(Ischarcmp())							//��������ַ���ȷ,�������ݲ����ô���
		{
			DateOut(revData);
	   	 	i=0;
			memset(buff,0,sizeof(buff));
			return;
		}
		else									//�������ȷ,���ô���
		{
			i=0;
			memset(buff,0,sizeof(buff));
			return;
		}

	}											 //�����յ�������
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






