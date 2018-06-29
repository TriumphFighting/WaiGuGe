#include"motor2.h"
#include"motor.h"
#include"usart1.h"
#include"usart2.h"
#include"usart3.h"
#include"usart4.h"
#include"usart5.h"
#include<stdio.h>



extern int AngleSpeed4;

void Speed2(u16 speed)//speed=3000,0-20000之间的值
{
	TIM_SetCompare2(TIM3,speed);
}

void Forward2(void)
{
  BK3=1;
//	EN3=0;
	FR3=0;
}

void Back2(void)
{
  BK3=1;
//	EN3=0;
	FR3=1;
}

void Stop2(void)
{
//  EN3=1;
	BK3=0;
}


				