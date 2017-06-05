#include "Beep.h"

void Beep(unchar t)
{
	unchar i;
	for(i=0;i<100;i++)
	{
		beep=~beep;
	   	DelayMs(t);
	}
	 beep=0;
}