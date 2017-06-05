#ifndef _GLOBLE_H_
#define _GLOBEL_H_

//#define unsigned char uchar
#include "STC15.h"
#include "intrins.h"

#define unchar unsigned char
#define uint unsigned int

//此处保存全局变量



/*-----位控制段-----*/


/*------------------------------*/

void Delay1us();
void Delay1ms();
void DelayUs(uint t) ;
void DelayMs(uint t) ;

#endif