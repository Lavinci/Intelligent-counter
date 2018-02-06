#include "Globle.h"
#include "intrins.h"
extern float Mi[10];   //保存九个班次的米数

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
	EA=0;					   //关中断
	IAP_CONTR=IAP_CONTR & 0x18;		   //0001,1000
	IAP_CONTR=IAP_CONTR | 0x01;		   //cpu硬件延时
	IAP_CONTR=IAP_CONTR | 0x80;			//ISPEN=1
}
void ISP_IAP_disable()
{
	 IAP_CONTR = IAP_CONTR & 0x7f;	//ISPEN=0
	 IAP_TRIG=0x00;
	 EA=1;//开中断
}
void IAPGoOn()
{
	ISP_IAP_enable();	 //打开IAP
	IAP_TRIG = 0x46;	//触发字节1
	IAP_TRIG = 0xb9;	//触发字节2
	_nop_();

}
unsigned char byte_read(unsigned int byte_addr)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);		
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);	//地址赋值
	IAP_CMD = IAP_CMD & 0xf8;		//清除低三位
	IAP_CMD = IAP_CMD | 0x01;	   //写入读指令
	IAPGoOn();						//触发执行
	ISP_IAP_disable();				 //关闭

	return (IAP_DATA);				   //返回数据
}
void byte_write(unsigned int byte_addr,unsigned char original_data)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);		
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);	//取地址
	IAP_CMD = IAP_CMD & 0xf8;		//清除低三位
	IAP_CMD = IAP_CMD | 0x02;	   //写入写指令
	IAP_DATA=original_data;			 //赋值
	IAPGoOn();						//触发执行
	ISP_IAP_disable();				 //关闭

}
void byte_earse(unsigned int byte_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr=(byte_addr & 0xfe00);
	IAP_ADDRH=(unsigned char)(iSectorAddr>>8);		
	IAP_ADDRL=0x00;
	IAP_CMD = IAP_CMD & 0xf8;		//清除低三位
	IAP_CMD = IAP_CMD | 0x03;	   //写入擦除指令
	IAPGoOn();						//触发执行
	ISP_IAP_disable();				 //关闭

}