#include "SN74LS595.h"
#include "intrins.h"

void DataSend(unsigned char da)
{

	unsigned char i;
	sclk=0;
	rck=0;

	for(i=8;i>0;i--)	//ѭ��8�Σ�дһ�ֽ�
	{
		ser=da & 0x80;	//����BIT0λ
		da<<=1;		//Ҫ���͵��������ƣ�׼��������һλ
		sclk=0;			//��λʱ��������
		_nop_();
		_nop_();
		sclk=1;
		_nop_();
		_nop_();
		sclk=0;
	}
	rck=0;	//�����ؽ������͵����������
	_nop_();
	_nop_();
	rck=1;
	_nop_();
	_nop_();
	rck=0;


}
