#ifndef _BEEP_H_
#define _BEEP_H_
#include "Globle.h"

sbit beep = P0^6;

void Beep(unsigned char t);

#endif