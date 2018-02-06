#ifndef _GLOBLE_H_
#define _GLOBEL_H_
#include "STC15.h"
#include "intrins.h"

void Delay1us();
void Delay1ms();
void DelayUs(unsigned int t) ;
void DelayMs(unsigned int t) ;
void miToma();
void maTomi();
//EEPROM
void ISP_IAP_enable();
void ISP_IAP_disable();
void IAPGoOn();
unsigned char byte_read(unsigned int byte_addr);
void byte_write(unsigned int byte_addr,unsigned char original_data);

void byte_earse(unsigned int byte_addr);
#endif