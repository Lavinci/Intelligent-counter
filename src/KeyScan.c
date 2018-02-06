#include "KeyScan.h"
#include "Beep.h"
#include "SN74LS595.h"
#include "Lcd.h"
#include "globle.h"
#include "Led.h"

extern enum State{
	eShow,
	eRun_Count=101,eRun_Length,
	eSet_Length,eSet_Xishu,eSet_Delay,eSet_Key
	}state;
extern float Mi[9];   //����Ÿ���ε�����
extern unsigned char banci;	//���
extern float speed;		//�ٶ�
extern float Xishu;
extern float DelayTime;
extern unsigned char mode;//0 mi,1ma
extern unsigned int Tnum;

//���ذ�����,����5���򷵻�10+x ,û���򷵻�0
unsigned char KeyScan()
{

	unsigned char num=0;

	ShowWei(0);		//��Ӱ
	if(KEY==0)
	{
		DelayMs(5);
			if(KEY==0)
			{
			Tnum=0;
			//	Beep(1);//������,�ǵ�ɾ��
			//��ʱ��ʼ
				DataSend(0x1E);	
					if(KEY==0)
						num=1;
				DataSend(0x1D);
					if(KEY==0)
						num=5;
				DataSend(0x1B);
					if(KEY==0)
						num=4;
				DataSend(0x17);
					if(KEY==0)
						num=3;
				DataSend(0x0F);
					if(KEY==0)
						num=2;
				DataSend(0);
  
				while(KEY==0)
				{

					switch(state)
					{
						case eRun_Count:
							ShowData(banci,Mi,mode,0);
							ShowSpeed(speed);
							break;
						case eSet_Length:
							ShowData(banci,Mi,mode,0);
							ShowSet(1);
							break;
						case eSet_Xishu:
							ShowDataSingle(banci,Xishu,mode,0);
							ShowSet(2);
							break;
						case eSet_Delay:
							ShowDataSingle(banci,DelayTime,mode,0);
							ShowSet(3);
							break;
					}  		 
				}	
			if(Tnum>40)//����2��,����
			{	
				if(num==1)
					num=11;	   //s�趨
				if(num==2)	   //�ۼ�
					num=12;
			}
			 Tnum=0;	
		}
	}
	return num;
}
