#ifndef  __DHT11_H__
#define  __DHT11_H__
#include "stdint.h"

void DHT11_PortOutput(void);
void DHT11_PortInput(void);
uint8_t DHT_Read_Byte(void);
uint8_t DHT_Read(void);

#endif
