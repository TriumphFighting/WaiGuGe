#include "beep.h"
#include "delay.h"

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrucyure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	
	GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrucyure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}


void Beep_StandUp(void)
{
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
}

void Beep_Walk(void)
{
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(100);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(100);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	delay_ms(100);
	BEEP=1;
	delay_ms(100);
	BEEP=0;
	
}

void Beep_SitDown(void)
{
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
	delay_ms(1000);
	BEEP=1;
	delay_ms(1000);
	BEEP=0;
}

void Beep_Stop(void)
{
	BEEP=0;
	delay_ms(500);
	BEEP=1;
	delay_ms(500);
	BEEP=0;
	delay_ms(500);
	BEEP=1;
	delay_ms(500);
	BEEP=0;
}

void Beep_AllInitFinish(void)
{
	BEEP=1;
	delay_ms(500);
	BEEP=0;
}
	