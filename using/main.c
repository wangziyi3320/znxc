#include "main.h"
u16 sd_value=0;
u32 JL=0;
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Config();//时钟初始化
	SystemInit();//初始化系统时钟为72MHZ	
	USART1Init();
	USART3Init(0);
	KEY_Init();
	TIM3_PWM_Init();
	LED_Init();
	LED1=LED2=LED3=1;	
	delay_init();	    	 //延时函数初始化
	//Timerx_Init(1,7199);//10Khz的计数频率，计数到5000为500ms 
	while(1)
	{	
	  key_SMG();
	  if(xx==0) //停止状态
	  {
		   SetMotorVoltageAndDirection(0,0);
			 yy=0;
			 LED1=LED2=LED3=1;
			 zz=1;
	  }	
	  if(xx==1)//运行状态：更具传感器的状态判断循迹的工作
	  {	LED1=0;//运行状态指示灯
			//红外循迹模式：小车卡着黑线循迹行走
			if(CG_Z1==1&&CG_Y1==1) //左右两个传感器都检测到黑线，小车执行停止
			{
			  SetMotorVoltageAndDirection(0,0);
			}
		  else
			if(CG_Z1==0&&CG_Y1==0)  //左右两个传感器都没有检测到黑线，小车执行前进
			{  
				SetMotorVoltageAndDirection(sd_value,sd_value);
			}	
		  else
			if(CG_Z1==1&&CG_Y1==0) //如果左传感器检测到黑线，表示小车车头偏左，为修正执行动作，小车执行右转的动作
			{
				SetMotorVoltageAndDirection(sd_value,sd_value-200);
			}	
			else
			if(CG_Z1==0&&CG_Y1==1) //如果右传感器检测到黑线，表示小车车头偏右，为修正执行动作，小车执行左转的动作
			{
				SetMotorVoltageAndDirection(sd_value-200,sd_value);
			}	
			 //速度状态指示
			 if(zz==1)//速度1档
			 {
			   LED2=1;LED3=0;sd_value=200;
			 }
			 else 
			 if(zz==2)//速度2档
			 {
			   LED2=0;LED3=1;sd_value=300;
			 }
			 else 
			 if(zz==3)//速度3档
			 {
			   LED2=0;LED3=0;sd_value=400;
			 } 
	  }
	 
  }
}

void RCC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//A3 A4 MOTORB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//B0 B1 MOTORA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//HC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //定时器时钟 pwm 控制电机

}



