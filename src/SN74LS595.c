#include "SN74LS595.h"
#include "intrins.h"

void DataSend(unsigned char da)
{

	unsigned char i;
	sclk=0;
	rck=0;

	for(i=8;i>0;i--)	//循环8次，写一字节
	{
		ser=da & 0x80;	//发送BIT0位
		da<<=1;		//要发送的数据右移，准备发送下一位
		sclk=0;			//移位时钟上升沿
		_nop_();
		_nop_();
		sclk=1;
		_nop_();
		_nop_();
		sclk=0;
	}
	rck=0;	//上升沿将数据送到输出锁存器
	_nop_();
	_nop_();
	rck=1;
	_nop_();
	_nop_();
	rck=0;


}
