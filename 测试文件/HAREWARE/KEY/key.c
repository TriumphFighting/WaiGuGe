#include "key.h"
#include "sys.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&GPIO_InitStrue);	
}

void KeyScan(void)
{
	A: if(KEY1==0)
			{
				delay_ms(10);
				if(KEY1==0)
				{
					while(KEY1==0);
				}
				else {goto A;}
			}
			else {goto A;}
}





