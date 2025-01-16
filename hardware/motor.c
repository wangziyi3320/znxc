#include "motor.h"

void Motor_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//初始化TB6612
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
	
}

/******************************************************
PWM模式（电机驱动）
配置TIM3复用输出PWM时用到的I/O
内部调用
***********************************************************/
static void TIM3_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}
/********************************************
配置TIM3输出的pwm信号的模式，周期 极性 占空比
内部调用
*********************************************************/
static void TIM3_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/*设置PWM信号电平跳变值*/
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM3 ARR Register = 71999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 1 KHz.
		CC1 update rate = TIM3 counter clock / CCR1_Val
    TIM3 Channelx duty cycle = (TIM3_CCRx/ TIM3_ARR)* 100 = x%
    
  ----------------------------------------------------------------------- */
	TIM_TimeBaseStructure.TIM_Period = 999; //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 3;	//设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM2 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	//设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平	

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	  //使能通道1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道3
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;   
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  //
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	  //使能通道4
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

	TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	

}

void TIM3_PWM_Init(void)
{
	Motor_GPIO_Config();
	TIM3_GPIO_Config();
	TIM3_MODE_Config();	
}


