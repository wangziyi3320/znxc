#include "control.h"

unsigned char g_cMotorDisable = 0;//值等于0是电机正常转动，否则停止

/*电机转速及方向控制函数*/
void  SetMotorVoltageAndDirection(int i16LeftVoltage, int i16RightVoltage)
{
	
	if(i16LeftVoltage > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14 );		//AIN1,AIN2		    
		GPIO_ResetBits(GPIOB, GPIO_Pin_15 );
		i16LeftVoltage = (-i16LeftVoltage);
	}
	
	if(i16RightVoltage > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12 );		//BIN0,BIN1		    
		GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
		i16RightVoltage = (-i16RightVoltage);
	}
	
	if(i16RightVoltage > MOTOR_OUT_MAX)
	{
		i16RightVoltage = MOTOR_OUT_MAX;
	}
	if(i16LeftVoltage > MOTOR_OUT_MAX)
	{
		i16LeftVoltage = MOTOR_OUT_MAX;
	}
	if(g_cMotorDisable)
	{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,0);
	}
	else 
	{
		TIM_SetCompare1(TIM3,i16RightVoltage);
		TIM_SetCompare2(TIM3,i16LeftVoltage);
	}
}

