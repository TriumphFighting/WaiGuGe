#include"timer.h"
#include"led.h"
#include"delay.h"
#include <math.h>
#include"usart1.h"
#include"usart2.h"
#include"foot.h"
#include<stdio.h>
#include<motor.h>


//extern struct SAngle 	stcAngle;
//extern struct SAngle 	stcAngle3;
//extern struct SAngle 	stcAngle4;
//extern struct SAngle 	stcAngle5;
//char str[100];

//int Presentvalue;
//int Presentvalue3;
//int Presentvalue4;
//int Presentvalue5;

u8 PWM_flag1;

  void TIM2_Update(u16 arr,u16 psc)
	{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	TIM_TimeBaseInitStrue.TIM_Period=arr;
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);
	}

void TIM2_InterRupt_Init( void)
{	
	NVIC_InitTypeDef NVIC_InitStrue;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
   TIM2_Update(799,71);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStrue);
	
	TIM_Cmd(TIM2,ENABLE);
}

//void TIM2_InterRupt_Init( u16 arr,u16 psc)
//{	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
//	NVIC_InitTypeDef NVIC_InitStrue;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//	
//	TIM_TimeBaseInitStrue.TIM_Period=arr;
//	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;
//	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	
//	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn;
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStrue);
//	
//	TIM_Cmd(TIM2,ENABLE);
//}


//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//				if(PWM_flag1==1)  
//				{
//						PUS1=~PUS1;
//				}
//				else PUS1=0;
//		PUS1=~PUS1;
//		 LED=~LED;
//		  Presentvalue=(float)stcAngle.Angle[0]/32768*180;
//		  Presentvalue3=(float)stcAngle3.Angle[0]/32768*180;
//		  Presentvalue4=(float)stcAngle4.Angle[0]/32768*180;
//		  Presentvalue5=(float)stcAngle5.Angle[0]/32768*180;
//	    sprintf(str,"角  度:串口2（X轴）:%d\r\n\r\n角  度:串口3（X轴）:%d\r\n\r\n角  度:串口4（X轴）:%d\r\n\r\n角  度:串口5（X轴）:%d\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n",Presentvalue,Presentvalue3,Presentvalue4,Presentvalue5);
////	  	UART1_Put_String(str);
//		  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	 }
//}