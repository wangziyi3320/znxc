#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "stm32f10x.h"
#include "motor.h"
#define MOTOR_OUT_MAX           999	   //ռ�ձ������ֵ
#define MOTOR_OUT_MIN         (-999)   //ռ�ձȸ����ֵ
void  SetMotorVoltageAndDirection(int i16LeftVoltage, int i16RightVoltage);
#endif


