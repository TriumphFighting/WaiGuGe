#include"usart2.h"
#include"led.h"
#include"beep.h"

u8 ReciveBuff[1];
extern u8 Up_Flag; 
extern u8 Go_Flag; 
extern u8 Down_Flag; 
extern u8 Stop_Flag;

//struct STime		stcTime;
//struct SAcc 		stcAcc;
//struct SGyro 		stcGyro;
//struct SAngle 	stcAngle;
//struct SMag 		stcMag;
//struct SDStatus stcDStatus;
//struct SPress 	stcPress;
//struct SLonLat 	stcLonLat;
//struct SGPSV 		stcGPSV;

void USART2_InterRupt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	USART_InitStrue.USART_BaudRate=9600;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;//8位字长
	USART_Init(USART2,&USART_InitStrue);
	
	USART_Cmd(USART2,ENABLE);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStrue);
}


void USART2_IRQHandler(void)
{	
		if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
		{	
				ReciveBuff[0]=USART_ReceiveData(USART2);
				USART_SendData(USART2,ReciveBuff[0]);
				switch(ReciveBuff[0])
			  {
					case 02:LED0=1;if(Go_Flag==0&&Down_Flag==0)Up_Flag=1;ReciveBuff[0]=0;break;			
					case 03:LED0=0;if(Up_Flag==0&&Down_Flag==0)Go_Flag=1;ReciveBuff[0]=0;break;
					case 05:LED0=1;if(Up_Flag==0&&Go_Flag==0)Down_Flag=1;ReciveBuff[0]=0;break;
					case 06:BEEP=1;if(Up_Flag==0&&Down_Flag==0&&Go_Flag==1)Stop_Flag=1;ReciveBuff[0]=0;break;
			  }
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	 	}
}



























//void CopeSerial2Data(unsigned char ucData)
//{
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	
//	ucRxBuffer[ucRxCnt++]=ucData;
//	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//数据不满11个，则返回
//	else
//	{
//		switch(ucRxBuffer[1])
//		{
//			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据共同体里面，从而实现数据的解析。
//			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
//			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
//			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
//			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
//			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
//			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
//			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
//		}
//		ucRxCnt=0;
//	}
//}	

//void USART2_IRQHandler(void)
//{		
//		if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
//		{	
////			 LED=~LED;
//			 CopeSerial2Data((unsigned char)USART2->DR);//处理数据
//			 USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	 	}
//}