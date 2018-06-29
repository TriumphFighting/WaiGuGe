#include"motor.h"

void Motor_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrucyure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOF,ENABLE);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStrucyure);
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStrucyure);
}

