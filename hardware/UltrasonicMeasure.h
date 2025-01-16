#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void Ultrasonic_TIM5_Cap_Init(u16 arr,u16 psc);
void UltrasonicWave_StartMeasure(void);
double UltrasonicMeasure_Length(void);

#endif

