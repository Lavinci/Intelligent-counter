#include "Beep.h"

void Beep(unsigned char t)
{
	unsigned char i;
	for(i=0;i<100;i++)
	{
		beep=~beep;
	   	DelayMs(t);
	}
	 beep=0;
}