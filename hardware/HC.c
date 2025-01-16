#include "HC.h"

void HC595_GPIO_Config(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//SDI,LCK,SCK
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//SDO
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//SDI，SCK，LCK都初始化为低电平，SDO初始化为高电平
	SDI0;			//初始化为低电平
	SCK0;		    //初始化为低电平
	LCK0;			//初始化为低电平
	SDO1;			//初始化为高电平，因为SDO是输入到单片机
	
}
/*************************************************************************************
*函数名：void ShiftInOneByte(void)
*功  能：串行移入一个字节的数据
*说  明：按照74hc595的时序将dat串行移入到Shift Register，但不锁存输出，
		 此函数是master bit first 先移入最高位
**************************************************************************************/
void ShiftInOneByte(unsigned char dat)
{
	unsigned char i;
	unsigned char tmp;
	tmp=dat;
	for(i=0;i<8;i++) 
	{
		if(tmp&0x80)		   //将一位数据送到SDI
		{
			SDI1;	
		}
		else
		{
			SDI0;
		}
                  
		SCK0;				  //在SCK的上升沿，将SDI移入到移位寄存器
		SCK1;

		tmp=(tmp<<1);		  //将tmp左移一位并保存到tmp
	}                                 
}
/*************************************************************************************
*函数名：void ShiftInOneByteAndLatch(unsigned char dat)
*功  能：串行移入一个字节的数据并锁存
*说  明：按照74hc595的时序将dat串行移入到Shift Register，并锁存输出，
		 此函数是master bit first 先移入最高位
**************************************************************************************/
void ShiftInOneByteAndLatch(unsigned char dat)
{
	unsigned char i;
	unsigned char tmp;
	tmp=dat;
	for(i=0;i<8;i++) 
	{
		if(tmp&0x80)		   //将一位数据送到SDI
		{
			SDI1;	
		}
		else
		{
			SDI0;
		}

		SCK0;				  //在SCK的上升沿，将SDI移入到移位寄存器
		SCK1;

		tmp=(tmp<<1);		  //将tmp左移一位并保存到tmp
	}
	LCK0;	  				  //锁存
	LCK1;
}
/*************************************************************************************
*函数名：void ShiftInTwoByteAndLatch(unsigned char dat)
*功  能：串行移入两个字节的数据并锁存
*说  明：按照74hc595的时序将dat串行移入到Shift Register，并锁存输出，
		 此函数是master bit first 先移入最高位
**************************************************************************************/
void ShiftInTwoByteAndLatch(unsigned char dat1,unsigned char dat2)
{
	ShiftInOneByte(dat1);	  //移入第一个字节
	ShiftInOneByte(dat2);	  //移入第二个字节
	LCK0;	  				  //锁存
	LCK1;
}
/*************************************************************************************
*函数名：void ShiftInOneArrayAndLatch(unsigned char dat)
*功  能：串行移入一个数组数据并锁存
*说  明：低位数组先移入
**************************************************************************************/
void ShiftInOneArrayAndLatch(unsigned char* arr,unsigned char len)
{
	unsigned char i;
	for(i=0;i<len;i++)
	{
		ShiftInOneByte(arr[i]);
	}
	LCK0;	  				  //锁存
	LCK1;
}

