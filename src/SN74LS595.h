#ifndef _SN74LS595_H_
#define _SN74LS595_H_
#include "Globle.h"

sbit sclk = P2^1;
sbit rck = P0^4;
sbit ser = P2^3;

void DataSend(unsigned char da);

#endif