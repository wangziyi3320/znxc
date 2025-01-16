#ifndef __HC_H__
#define __HC_H__
#include "stm32f10x.h"

#define SCK0 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
#define SCK1 GPIO_SetBits(GPIOC,GPIO_Pin_13);

#define LCK0 GPIO_ResetBits(GPIOC,GPIO_Pin_14);
#define LCK1 GPIO_SetBits(GPIOC,GPIO_Pin_14);

#define SDI0 GPIO_ResetBits(GPIOC,GPIO_Pin_15);
#define SDI1 GPIO_SetBits(GPIOC,GPIO_Pin_15);

#define SDO0 GPIO_ResetBits(GPIOA,GPIO_Pin_0);
#define SDO1 GPIO_SetBits(GPIOA,GPIO_Pin_0);

void HC595_GPIO_Config(void);

void ShiftInOneByteAndLatch(unsigned char dat);
void ShiftInTwoByteAndLatch(unsigned char dat1,unsigned char dat2);
void ShiftInOneArrayAndLatch(unsigned char* arr,unsigned char len);


#endif

