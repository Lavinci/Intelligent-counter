
#include "Date.h"
#include "Beep.h"

extern float Mi[10];   //����Ÿ���ε�����
extern float speed;		//�ٶ�
extern float Total;	//�ܳ�
extern unsigned char  mode;//0 mi,1ma

void DateIn();//�ӹ��������õ�����

void DateOut(unsigned char _banci)
{
	unsigned char i;


 /************������******************/
	DataSOut(0x55);
	DataSOut(0xAA);	
 	DataSOut(0x20);	
/**************֡����****************/
	DataSOut(0x0C);	
/**************״̬��****************/

//�ֱ��ʹ���δʵ��,��Ϊ0.1
	if(!mode)//mi
		DataSOut(0x01);
	else
		DataSOut(0x00);

/**************����****************/
	DataSOut((long)(Mi[_banci]*10) >>16 );	   //���ֽ�	 ..6λ����λһ��Ϊ��
	DataSOut(  ((long)(Mi[_banci]*10) >>8)%256   );			//���ֽ�(ͷһ�μ�0.0)
	DataSOut( (long)(Mi[_banci]*10) %256);	//���ֽ�
/**************�ٶ�	******************/	
	DataSOut( (long)(speed)>>8);
	DataSOut( (long)(speed) %256);	 
/**************���******************/	
	DataSOut(_banci);
/**************У����****************/			
	DataSOut(0x00);	   //û��������ʲôУ����

/************************************/	
}
void DataSOut(unsigned char i)
{
   	SBUF=i;
	while(!TI);
	TI=0; 
}