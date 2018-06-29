#ifndef _TIMER_H
#define _TIMER_H
#include"sys.h"

void TIM2_InterRupt_Init( void);
void TIM2_Update(u16 arr,u16 psc);

#endif