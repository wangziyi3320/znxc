#ifndef __SMG_H__
#define __SMG_H__

#include "stm32f10x.h"
#include "HC.h"
#include "delay.h"

/*---------------------------��������---------------------------------------------------*/

extern unsigned char  Seg_test[8];			//�˶�����ܵ�ÿһ��
extern unsigned char  Dign[8];				//��λ����������
extern unsigned char  Number_arr[10];		//����0-9���߶�����ܵı�������
extern unsigned char  Character_arr[53];	//����ܿ���ʾ�ַ����˶�����ܵı������飬
//����_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u

void DisplayInterfaceInit(void);
void DisplayDatOnDign(unsigned char dign,unsigned char dat);
void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot);
void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot);

void Menu(unsigned char x, unsigned char y, unsigned char z,unsigned char weishu);

#endif
