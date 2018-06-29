#include"usart1.h"
#include<string.h>

static unsigned char TxBuffer[256];
static unsigned char count=0;
static unsigned char TxCounter=0;



struct STime1		stcTime1;
struct SAcc1 		stcAcc1;
struct SGyro1		stcGyro1;
struct SAngle1	stcAngle1;
struct SMag1		stcMag1;
struct SDStatus1 stcDStatus1;
struct SPress1 	stcPress1;
struct SLonLat1 	stcLonLat1;
struct SGPSV1		stcGPSV1;



void USART1_InterRupt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStru;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStru);
	
	GPIO_InitStru.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStru.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStru);
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStrue);
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStrue);
}


void CopeSerial1Data(unsigned char ucData)
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
			case 0x50:	memcpy(&stcTime1,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc1,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro1,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle1,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag1,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus1,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress1,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat1,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV1,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}


void USART1_IRQHandler(void)
{
 	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //?óê?μ?êy?Y
	{	 
		CopeSerial1Data((unsigned char)USART1->DR);//处理数据
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}


int GetPresentAngle1(void)
{
	static int PresentAngle1;
	PresentAngle1=(float)stcAngle1.Angle[0]/32768*180;
	return PresentAngle1;
}




/*串口1打印UART1_Put_String(str);
void UART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
}


void UART1_Put_String(unsigned char *Str)
{
	while(*Str)
	{
		if(*Str=='\r')UART1_Put_Char(0x0d);
			else if(*Str=='\n')UART1_Put_Char(0x0a);
				else UART1_Put_Char(*Str);
		Str++;
	}
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART1, TxBuffer[TxCounter++]); 
    if(TxCounter == count) 
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// 全部发送完成
		}
    USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
}
*/

