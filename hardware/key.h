#ifndef __KEY_H_
#define __KEY_H_
extern signed char xx ,yy,zz;

#include "stm32f10x.h"
#include "delay.h"
#include  "stdio.h"
#include "SMG.h"

#define Key0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取按键0
#define Key1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键1 
#define Key2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//读取按键2 

extern unsigned char   key_value;
extern signed char xx,yy,zz;

void KEY_Init(void) ;
u8 KEY_Scan(u8 mode);
void key_SMG(void);
#endif


