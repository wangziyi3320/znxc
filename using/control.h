#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "stm32f10x.h"
#include "motor.h"
#define MOTOR_OUT_MAX           999	   //占空比正最大值
#define MOTOR_OUT_MIN         (-999)   //占空比负最大值
void  SetMotorVoltageAndDirection(int i16LeftVoltage, int i16RightVoltage);
#endif


