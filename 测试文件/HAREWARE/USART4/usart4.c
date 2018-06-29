#include"usart4.h"
#include<string.h>


struct STime4		stcTime4;
struct SAcc4 		stcAcc4;
struct SGyro4 		stcGyro4;
struct SAngle4 	stcAngle4;
struct SMag4		stcMag4;
struct SDStatus4 stcDStatus4;
struct SPress4 	stcPress4;
struct SLonLat4 	stcLonLat4;
struct SGPSV4		stcGPSV4;

void USART4_InterRupt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStru;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStru);
	
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStru);
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	USART_Init(UART4,&USART_InitStrue);
	
	USART_Cmd(UART4,ENABLE);
	
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
}

void CopeSerial4Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x50:	memcpy(&stcTime4,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc4,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro4,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle4,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag4,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus4,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress4,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat4,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV4,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}	

void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!= RESET)
	{
		CopeSerial4Data((unsigned char)UART4->DR);//处理数据
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	}
}



int GetPresentAngle4(void)
{
	static int PresentAngle4;
	PresentAngle4=(float)stcAngle4.Angle[0]/32768*180;
	return PresentAngle4;
}