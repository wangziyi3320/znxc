
#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32f10x.h"
#include "delay.h"

extern int Distance;


void TIM1_Cap_Init(void);	
void Read_Distane(void);
char InfraredDetect(void);
void UltraSelfCheck(void);
int IsUltraOK(void);



#endif

