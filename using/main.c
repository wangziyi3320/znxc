#include "main.h"
u16 sd_value=0;
u32 JL=0;
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Config();//ʱ�ӳ�ʼ��
	SystemInit();//��ʼ��ϵͳʱ��Ϊ72MHZ	
	USART1Init();
	USART3Init(0);
	KEY_Init();
	TIM3_PWM_Init();
	LED_Init();
	LED1=LED2=LED3=1;	
	delay_init();	    	 //��ʱ������ʼ��
	//Timerx_Init(1,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	while(1)
	{	
	  key_SMG();
	  if(xx==0) //ֹͣ״̬
	  {
		   SetMotorVoltageAndDirection(0,0);
			 yy=0;
			 LED1=LED2=LED3=1;
			 zz=1;
	  }	
	  if(xx==1)//����״̬�����ߴ�������״̬�ж�ѭ���Ĺ���
	  {	LED1=0;//����״ָ̬ʾ��
			//����ѭ��ģʽ��С�����ź���ѭ������
			if(CG_Z1==1&&CG_Y1==1) //������������������⵽���ߣ�С��ִ��ֹͣ
			{
			  SetMotorVoltageAndDirection(0,0);
			}
		  else
			if(CG_Z1==0&&CG_Y1==0)  //����������������û�м�⵽���ߣ�С��ִ��ǰ��
			{  
				SetMotorVoltageAndDirection(sd_value,sd_value);
			}	
		  else
			if(CG_Z1==1&&CG_Y1==0) //����󴫸�����⵽���ߣ���ʾС����ͷƫ��Ϊ����ִ�ж�����С��ִ����ת�Ķ���
			{
				SetMotorVoltageAndDirection(sd_value,sd_value-200);
			}	
			else
			if(CG_Z1==0&&CG_Y1==1) //����Ҵ�������⵽���ߣ���ʾС����ͷƫ�ң�Ϊ����ִ�ж�����С��ִ����ת�Ķ���
			{
				SetMotorVoltageAndDirection(sd_value-200,sd_value);
			}	
			 //�ٶ�״ָ̬ʾ
			 if(zz==1)//�ٶ�1��
			 {
			   LED2=1;LED3=0;sd_value=200;
			 }
			 else 
			 if(zz==2)//�ٶ�2��
			 {
			   LED2=0;LED3=1;sd_value=300;
			 }
			 else 
			 if(zz==3)//�ٶ�3��
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��ʱ��ʱ�� pwm ���Ƶ��

}



