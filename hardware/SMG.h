#ifndef __SMG_H__
#define __SMG_H__

#include "stm32f10x.h"
#include "HC.h"
#include "delay.h"

/*---------------------------声明数组---------------------------------------------------*/

extern unsigned char  Seg_test[8];			//八段数码管的每一段
extern unsigned char  Dign[8];				//对位的译码数组
extern unsigned char  Number_arr[10];		//数字0-9到七段数码管的编码数组
extern unsigned char  Character_arr[53];	//数码管可显示字符到八段数码管的编码数组，
//包括_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u

void DisplayInterfaceInit(void);
void DisplayDatOnDign(unsigned char dign,unsigned char dat);
void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot);
void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot);

void Menu(unsigned char x, unsigned char y, unsigned char z,unsigned char weishu);

#endif
