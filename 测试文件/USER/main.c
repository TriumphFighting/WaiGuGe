#include "key.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
//#include "timer.h"
//#include"timer5.h"
#include"pwm.h"
#include"usart1.h"
#include"usart2.h"
#include"usart3.h"
#include"usart4.h"
#include"usart5.h"
#include"foot.h"
#include"motor.h"

extern u8 Up_Flag; 
extern u8 Go_Flag; 
extern u8 Stop_Flag;
extern u8 Down_Flag;

u8 RaiseLegFlag=1;
u8 GoHomeFlag=1;
//I am Chinese,i love my motherland
int main(void)
{   
    delay_ms(100);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		PWM_GPIO_Configuration();
		Motor_GPIO_Init();
    TIM3_Configuration();
    NVIC_Configuration();
	  LED_Init();
		Beep_Init();
	  KEY_Init();   	
		USART1_InterRupt_Init();
	  USART2_InterRupt_Init();
	  USART3_InterRupt_Init();
		USART4_InterRupt_Init();
	  USART5_InterRupt_Init();
		delay_ms(300);
//	KeyScan();
		LED0=0;
		Beep_AllInitFinish();
//	UART1_Put_String("        准备完成......\r\n\r\n");
	  while(1)
		{
				//原点复位
				if(GoHomeFlag==1)
				{
					AutoGoHome();
					GoHomeFlag=0;
				}				
				//起立
				if(Up_Flag==1)
				{
						Beep_StandUp();
//					UART1_Put_String("起立\r\n");
						UpConfig();
						FourAxisCarryOut();
						Up_Flag=0;
				}
				else if(Go_Flag==1)//行走
				{					
//					UART1_Put_String("行走\r\n");
						//弯腰抬腿
						if(RaiseLegFlag==1)
						{
							Beep_Walk();
							//弯腰
							BowConfig();
							GoConfig();
							FourAxisCarryOut();											
							delay_ms(3000);							
							//抬腿
							RaiseLegConfig();
							GoConfig();
							FourAxisCarryOut();
							
							RaiseLegFlag=0;
						}
						//循环行走
						WalkCycleConfig();
						GoConfig();
						FourAxisCarryOut();
						//停    止
						if(Stop_Flag==1)
						{
							//双腿并拢
							MergeLegConfig();
							GoConfig();
						  FourAxisCarryOut();							
							Beep_Stop();
							//双腿直立
							UpRightLegConfig();
							GoConfig();
						  FourAxisCarryOut();
							
							Go_Flag=0;
							Stop_Flag=0;
							RaiseLegFlag=1;
						}
				}
				else if(Down_Flag==1)//蹲下
				{
						Beep_SitDown();
//					UART1_Put_String("蹲下\r\n");
						DownConfig();
						FourAxisCarryOut();
						Down_Flag=0;
				}
		}				
}