
#include "Date.h"
#include "Beep.h"

extern float Mi[10];   //保存九个班次的米数
extern float speed;		//速度
extern float Total;	//总长
extern unsigned char  mode;//0 mi,1ma

void DateIn();//从光电编码器得到数据

void DateOut(unsigned char _banci)
{
	unsigned char i;


 /************启动码******************/
	DataSOut(0x55);
	DataSOut(0xAA);	
 	DataSOut(0x20);	
/**************帧长度****************/
	DataSOut(0x0C);	
/**************状态码****************/

//分辨率功能未实现,均为0.1
	if(!mode)//mi
		DataSOut(0x01);
	else
		DataSOut(0x00);

/**************计数****************/
	DataSOut((long)(Mi[_banci]*10) >>16 );	   //高字节	 ..6位数高位一定为零
	DataSOut(  ((long)(Mi[_banci]*10) >>8)%256   );			//中字节(头一次见0.0)
	DataSOut( (long)(Mi[_banci]*10) %256);	//低字节
/**************速度	******************/	
	DataSOut( (long)(speed)>>8);
	DataSOut( (long)(speed) %256);	 
/**************班次******************/	
	DataSOut(_banci);
/**************校验码****************/			
	DataSOut(0x00);	   //没看明白是什么校验码

/************************************/	
}
void DataSOut(unsigned char i)
{
   	SBUF=i;
	while(!TI);
	TI=0; 
}