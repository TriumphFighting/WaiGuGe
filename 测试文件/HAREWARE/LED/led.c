#include "led.h"
#include "sys.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrucyure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);	
	
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStrucyure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}







