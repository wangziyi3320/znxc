#ifndef __HCSR_H
#define __HCSR_H
#include "sys.h"

#define HCSR04_PORT     GPIOA
#define HCSR04_CLK      RCC_APB2Periph_GPIOA
#define HCSR04_TRIG     GPIO_Pin_2
#define HCSR04_ECHO     GPIO_Pin_11

#define TRIG_Send  PAout(2) 
#define ECHO_Reci  PAin(11)


void hcsr04_NVIC(void);
float Hcsr04GetLength(void );
void Hcsr04Init(void);

#endif

