#ifndef __CGQ_H
#define __CGQ_H	 
#include "sys.h"

#define CG_Z1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define CG_Z2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
//#define CG_Z3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define CG_Y1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define CG_Y2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
void CGQ_Init(void);//≥ı ºªØ

		 				    
#endif
