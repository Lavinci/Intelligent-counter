#include "Globle.h"
#include "intrins.h"
extern float Mi[10];   //����Ÿ���ε�����

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


void DelayUs(unsigned int t)
{
	for(t;t>0;t--)
		Delay1us();
}
void DelayMs(unsigned int t)
{
	for(t;t>0;t--)
		Delay1ms();
}  


void miToma()
{
	int i;
	for(i=0;i<10;i++)
		Mi[i]*=1.09;
}
void maTomi()
{
	int i;
	for(i=0;i<10;i++)
	Mi[i]/=1.09;

}

/******************EEPROM******************/
void ISP_IAP_enable()
{
	EA=0;					   //���ж�
	IAP_CONTR=IAP_CONTR & 0x18;		   //0001,1000
	IAP_CONTR=IAP_CONTR | 0x01;		   //cpuӲ����ʱ
	IAP_CONTR=IAP_CONTR | 0x80;			//ISPEN=1
}
void ISP_IAP_disable()
{
	 IAP_CONTR = IAP_CONTR & 0x7f;	//ISPEN=0
	 IAP_TRIG=0x00;
	 EA=1;//���ж�
}
void IAPGoOn()
{
	ISP_IAP_enable();	 //��IAP
	IAP_TRIG = 0x46;	//�����ֽ�1
	IAP_TRIG = 0xb9;	//�����ֽ�2
	_nop_();

}
unsigned char byte_read(unsigned int byte_addr)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);		
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);	//��ַ��ֵ
	IAP_CMD = IAP_CMD & 0xf8;		//�������λ
	IAP_CMD = IAP_CMD | 0x01;	   //д���ָ��
	IAPGoOn();						//����ִ��
	ISP_IAP_disable();				 //�ر�

	return (IAP_DATA);				   //��������
}
void byte_write(unsigned int byte_addr,unsigned char original_data)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);		
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);	//ȡ��ַ
	IAP_CMD = IAP_CMD & 0xf8;		//�������λ
	IAP_CMD = IAP_CMD | 0x02;	   //д��дָ��
	IAP_DATA=original_data;			 //��ֵ
	IAPGoOn();						//����ִ��
	ISP_IAP_disable();				 //�ر�

}
void byte_earse(unsigned int byte_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr=(byte_addr & 0xfe00);
	IAP_ADDRH=(unsigned char)(iSectorAddr>>8);		
	IAP_ADDRL=0x00;
	IAP_CMD = IAP_CMD & 0xf8;		//�������λ
	IAP_CMD = IAP_CMD | 0x03;	   //д�����ָ��
	IAPGoOn();						//����ִ��
	ISP_IAP_disable();				 //�ر�

}