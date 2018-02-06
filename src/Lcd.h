#ifndef _LCD_H_
#define _LCD_H_
#include "Globle.h"
	

void ShowWei(unsigned char wei);
void ShowData(unsigned char banci,float* Mi,unsigned char mode,unsigned char _flashWei);
void ShowDataSingle(unsigned char banci,float num,unsigned char mode,unsigned char _flashWei);
void ShowKeyEv(bit _KeyEv);
void ShowSpeed(float speed);
void ShowSet(unsigned char _i);

#endif