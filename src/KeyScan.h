#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_
#include "Globle.h"

sbit KEY = P1^2;

unsigned char KeyScan();
extern void ExecuteKeyNum();

#endif