#include "ultrasonicMeasure.h"
#include "delay.h"
#include "usart.h"


//PA0  ECH0
//PA1  TRIG


//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM5_ICInitStructure;//����TIM_ICInit�Ľṹ�壨ΪʲôҪ�����棩

void Ultrasonic_TIM5_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO_Init�Ľṹ��
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����TIM_TimeBaseInit�Ľṹ��
	
	NVIC_InitTypeDef NVIC_InitStructure;//�ж����ȼ�����NVIC_Init�ṹ�����
	
	//��ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	//��ʼ��GPIO��   ��Ϊ����ȡ�����ⲿ�����ٶȣ����������ٶ���
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;         //PA0 ECH0  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;					 //PA1��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOA, &GPIO_InitStructure);	                 //��ʼ������GPIO 
	
	//Ĭ��Ϊ�͵�ƽ��ֻ�а�������ʱ�����ߵ�ƽ
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);             //PA0����
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//�����µģ���ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������ƵΪ����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
	
}



u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	 
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //����¼������ۿ�ʼ�˲��񣬻�û�в�����ɣ�������������ִ�У�
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;    //��һ�����ʱ��
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//�ٲ���1���������¼�  
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//�ݲ���һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����  ������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,�ڵ�һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);             //��������ֵ��Ϊ0
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ  �߱�־��һ�����
 
}


double Ultrasonic_Length; //������������ĳ���

double UltrasonicMeasure_Length(void)
{
	
		u32 temp=0;
		delay_ms(10);
		
		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺͣ����һ�μ���65536��
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ�� us
			//��ʽΪ  ����=�ߵ�ƽʱ��*����/2
			Ultrasonic_Length = temp*340/20000; //��λΪcm
//			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
		
		return Ultrasonic_Length;
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(GPIOA,GPIO_Pin_1); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
}




