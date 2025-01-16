#include "key.h"
unsigned char   key_value=0;
signed char xx = 0,yy = 0,zz = 0;

void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  	
}
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(Key0==0||Key1==0||Key2==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(Key0==0)				//GPIO12	
			return key_value =1;	
		else if(Key1==0) //GPIO13 
			return key_value = 2;
		else if(Key2==0) //GPIO14
			return key_value = 3;
	}
	else if(Key0==1&&Key1==1&&Key2==1)
	key_up=1; 	    
 	return 0;// �ް�������
}
void key_SMG(void)
{
		KEY_Scan(0);
		if(key_value == 1)
		{
			key_value = 255;
			xx=1;				
		}
		if(key_value == 2)
		{
			key_value = 255;
			xx=0;		
		}
		if(key_value == 3)
		{
			key_value = 255;
				zz++;
				if(zz>3)
					zz=1;
		}
}

