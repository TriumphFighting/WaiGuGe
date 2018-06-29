#include"pwm.h"
#include"foot.h"

u16 ToggleTime_axis1;//Öá1
u32 PulseCounter_axis1;

u16 ToggleTime_axis2;//Öá2
u32 PulseCounter_axis2;

u16 ToggleTime_axis3;//Öá3
u32 PulseCounter_axis3;

u16 ToggleTime_axis4;//Öá4
u32 PulseCounter_axis4;

void PWM_GPIO_Configuration(void)   
{ 
	GPIO_InitTypeDef GPIO_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrue);
}

void TIM3_Configuration(void)
{  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
   
	TIM_TimeBaseStructure.TIM_Period =0xFFFF;                                                         
	TIM_TimeBaseStructure.TIM_Prescaler =3;         
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
	
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//Öá1
	TIM_OCInitStructure.TIM_Pulse = ToggleTime_axis1 ;
	TIM_OC1Init(TIM3, & TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Disable) ;     
	
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//Öá2
	TIM_OCInitStructure.TIM_Pulse = ToggleTime_axis2 ;
	TIM_OC2Init(TIM3, & TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Disable) ; 
	
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//Öá3
	TIM_OCInitStructure.TIM_Pulse = ToggleTime_axis3 ;
	TIM_OC3Init(TIM3, & TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable) ; 
	
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//Öá4
	TIM_OCInitStructure.TIM_Pulse = ToggleTime_axis4 ;
	TIM_OC4Init(TIM3, & TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable) ; 
	
	TIM_Cmd(TIM3, DISABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);  
}

void NVIC_Configuration(void)   
{      
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);     
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
  NVIC_Init(&NVIC_InitStructure);                             
}

void TIM3_IRQHandler(void)
{  u16 reloadvalue;
   if(TIM_GetITStatus(TIM3,TIM_IT_CC1)!=RESET)//Öá1
   {      
		 TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
     reloadvalue=TIM_GetCapture1(TIM3);
     TIM_SetCompare1(TIM3,reloadvalue+ToggleTime_axis1 );     
		 PulseCounter_axis1++;
   }
	 if(TIM_GetITStatus(TIM3,TIM_IT_CC2)!=RESET)//Öá2
	 {
		 TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);
		 reloadvalue=TIM_GetCapture2(TIM3);
		 TIM_SetCompare2(TIM3,reloadvalue+ToggleTime_axis2 );
		 PulseCounter_axis2++;
	 }
	 if(TIM_GetITStatus(TIM3,TIM_IT_CC3)!=RESET)//Öá3
	 {
		 TIM_ClearITPendingBit(TIM3,TIM_IT_CC3);
		 reloadvalue=TIM_GetCapture3(TIM3);
		 TIM_SetCompare3(TIM3,reloadvalue+ToggleTime_axis3 );
		 PulseCounter_axis3++;
	 }
	 if(TIM_GetITStatus(TIM3,TIM_IT_CC4)!=RESET)//Öá4
	 {
		 TIM_ClearITPendingBit(TIM3,TIM_IT_CC4);
		 reloadvalue=TIM_GetCapture4(TIM3);
		 TIM_SetCompare4(TIM3,reloadvalue+ToggleTime_axis4 );
		 PulseCounter_axis4++;
	 }
}
