#include"usart3.h"
#include<string.h>


struct STime3		stcTime3;
struct SAcc3 		stcAcc3;
struct SGyro3 		stcGyro3;
struct SAngle3 	stcAngle3;
struct SMag3 		stcMag3;
struct SDStatus3 stcDStatus3;
struct SPress3 	stcPress3;
struct SLonLat3 	stcLonLat3;
struct SGPSV3 		stcGPSV3;


void USART3_InterRupt_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitValue;
	USART_InitTypeDef USART_InitValue;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	//GPIO端口设置
	GPIO_InitValue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitValue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitValue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitValue);
	
  GPIO_InitValue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitValue.GPIO_Pin =GPIO_Pin_11;
  GPIO_Init(GPIOB,&GPIO_InitValue);
  
	USART_InitValue.USART_BaudRate =115200;
  USART_InitValue.USART_WordLength = USART_WordLength_8b;
  USART_InitValue.USART_StopBits = USART_StopBits_1;
  USART_InitValue.USART_Parity = USART_Parity_No;
  USART_InitValue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitValue.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART3,&USART_InitValue);
	USART_ClearFlag(USART3,USART_FLAG_TC); 
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//配置串口接收非空中断
	
  NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn ; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2; //抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;   //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //使能USART3中断
  NVIC_Init(&NVIC_InitStructure);  
	
  USART_Cmd(USART3,ENABLE);
}


void CopeSerial3Data(unsigned char ucData)
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
			case 0x50:	memcpy(&stcTime3,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc3,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro3,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle3,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag3,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus3,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress3,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat3,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV3,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}	


void USART3_IRQHandler(void)
{
 	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
	{	 
		CopeSerial3Data((unsigned char)USART3->DR);//处理数据
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}

int GetPresentAngle3(void)
{
	static int PresentAngle3;
	PresentAngle3=(float)stcAngle3.Angle[0]/32768*180;
	return PresentAngle3;
}