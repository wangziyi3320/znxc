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
//SDI��SCK��LCK����ʼ��Ϊ�͵�ƽ��SDO��ʼ��Ϊ�ߵ�ƽ
	SDI0;			//��ʼ��Ϊ�͵�ƽ
	SCK0;		    //��ʼ��Ϊ�͵�ƽ
	LCK0;			//��ʼ��Ϊ�͵�ƽ
	SDO1;			//��ʼ��Ϊ�ߵ�ƽ����ΪSDO�����뵽��Ƭ��
	
}
/*************************************************************************************
*��������void ShiftInOneByte(void)
*��  �ܣ���������һ���ֽڵ�����
*˵  ��������74hc595��ʱ��dat�������뵽Shift Register���������������
		 �˺�����master bit first ���������λ
**************************************************************************************/
void ShiftInOneByte(unsigned char dat)
{
	unsigned char i;
	unsigned char tmp;
	tmp=dat;
	for(i=0;i<8;i++) 
	{
		if(tmp&0x80)		   //��һλ�����͵�SDI
		{
			SDI1;	
		}
		else
		{
			SDI0;
		}
                  
		SCK0;				  //��SCK�������أ���SDI���뵽��λ�Ĵ���
		SCK1;

		tmp=(tmp<<1);		  //��tmp����һλ�����浽tmp
	}                                 
}
/*************************************************************************************
*��������void ShiftInOneByteAndLatch(unsigned char dat)
*��  �ܣ���������һ���ֽڵ����ݲ�����
*˵  ��������74hc595��ʱ��dat�������뵽Shift Register�������������
		 �˺�����master bit first ���������λ
**************************************************************************************/
void ShiftInOneByteAndLatch(unsigned char dat)
{
	unsigned char i;
	unsigned char tmp;
	tmp=dat;
	for(i=0;i<8;i++) 
	{
		if(tmp&0x80)		   //��һλ�����͵�SDI
		{
			SDI1;	
		}
		else
		{
			SDI0;
		}

		SCK0;				  //��SCK�������أ���SDI���뵽��λ�Ĵ���
		SCK1;

		tmp=(tmp<<1);		  //��tmp����һλ�����浽tmp
	}
	LCK0;	  				  //����
	LCK1;
}
/*************************************************************************************
*��������void ShiftInTwoByteAndLatch(unsigned char dat)
*��  �ܣ��������������ֽڵ����ݲ�����
*˵  ��������74hc595��ʱ��dat�������뵽Shift Register�������������
		 �˺�����master bit first ���������λ
**************************************************************************************/
void ShiftInTwoByteAndLatch(unsigned char dat1,unsigned char dat2)
{
	ShiftInOneByte(dat1);	  //�����һ���ֽ�
	ShiftInOneByte(dat2);	  //����ڶ����ֽ�
	LCK0;	  				  //����
	LCK1;
}
/*************************************************************************************
*��������void ShiftInOneArrayAndLatch(unsigned char dat)
*��  �ܣ���������һ���������ݲ�����
*˵  ������λ����������
**************************************************************************************/
void ShiftInOneArrayAndLatch(unsigned char* arr,unsigned char len)
{
	unsigned char i;
	for(i=0;i<len;i++)
	{
		ShiftInOneByte(arr[i]);
	}
	LCK0;	  				  //����
	LCK1;
}

