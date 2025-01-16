#include "hcsr04.h"
#include "delay.h"
#include "timer.h"

u32 Time2_count1=0;

//����ģ��

u16 msHcCount = 0;//ms����
void hcsr04_NVIC()
{
            NVIC_InitTypeDef NVIC_InitStructure;
            NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
            NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
            NVIC_Init(&NVIC_InitStructure);
}


static void OpenTimerForHc()     
{
        TIM_SetCounter(TIM2,0);
        msHcCount = 0;
        TIM_Cmd(TIM2, ENABLE);  
}
 
static void CloseTimerForHc()        
{
        TIM_Cmd(TIM2, DISABLE);  
}
 


void TIM2_IRQHandler(void)   
{
        if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
        {
                TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
                msHcCount++;	
        }
}
 
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;
        t += TIM_GetCounter(TIM2);
          TIM2->CNT = 0;  
          delay_ms(60);
        return t;
}
 
float Hcsr04GetLength(void )
{
   u32 t = 0;
   int i = 0;
   float lengthTemp = 0;
	 float sum = 0;
   while(i!=5)
	 {      		
			TRIG_Send = 1;      
			delay_us(20);
			TRIG_Send = 0;		
      while(ECHO_Reci == 0);      
      OpenTimerForHc();       
      i = i + 1;
      while(ECHO_Reci == 1);
      CloseTimerForHc();        
      t = GetEchoTimer();
			lengthTemp = 331.3875*100/1000000*(float)t/2;				
      sum = lengthTemp + sum ;      
   }
			lengthTemp = sum/5;
			return lengthTemp;
}

void Hcsr04Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //�������ڶ�ʱ���Ľṹ��
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);
     
        //IO��ʼ��
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;       //���͵�ƽ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
     
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;     //���ص�ƽ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  
    GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);    
     
            //��ʱ����ʼ�� ʹ�û�����ʱ��TIM2
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //ʹ��RCCʱ��
        //���ö�ʱ�������ṹ��
	
        TIM_DeInit(TIM2);
//        TIM_TimeBaseStructure.TIM_Period = (65536-1);
        TIM_TimeBaseStructure.TIM_Period = (1000-1);
        TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 

				
        TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);          
        
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);   
        TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    
        hcsr04_NVIC();
        TIM_Cmd(TIM2,DISABLE);     
}



