#include"usart5.h"
#include<string.h>


struct STime5		stcTime5;
struct SAcc5 		stcAcc5;
struct SGyro5 		stcGyro5;
struct SAngle5 	stcAngle5;
struct SMag5		stcMag5;
struct SDStatus5 stcDStatus5;
struct SPress5 	stcPress5;
struct SLonLat5 	stcLonLat5;
struct SGPSV5		stcGPSV5;

void USART5_InterRupt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	
	//GPIO???������??
	//UART5_TX   PC.12
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //��?3??��?��50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //��?������?3??�꨺? Out_PP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;      //??UART4 ��?TX ?????a?�䨮?��?������?3? AF_PP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//??UART5 ��?RX ?????a?�䨮?????��?��? IN_FLOATING
	//UART5_RX	  PD.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //????��?��? IN_FLOATING 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = 115200; //2����??��
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //��?3��8??
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1??����?1��??��
	USART_InitStructure.USART_Parity = USART_Parity_No; //?T????D��?��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //?T����????
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�䨰?aRx?����?o��Tx����?��1|?��
	
	USART_Init(UART5 , &USART_InitStructure);
	
	/* Enable the UART5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//?��??��??��??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//������??��??3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ�����̨���1?��
	NVIC_Init(&NVIC_InitStructure);	//?��?Y???����?2?��y3?��??��VIC??��??��
	
//	USART_ClearFlag(UART5,USART_FLAG_TC); 
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//????��??��?����?��????D??
	
	USART_Cmd(UART5,ENABLE);

}

void CopeSerial5Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x50:	memcpy(&stcTime5,&ucRxBuffer[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݹ�ͬ�����棬�Ӷ�ʵ�����ݵĽ�����
			case 0x51:	memcpy(&stcAcc5,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro5,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle5,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag5,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus5,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress5,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat5,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV5,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}


void UART5_IRQHandler(void)
{
 	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //?����?��?��y?Y
	{	 
		CopeSerial5Data((unsigned char)UART5->DR);//��������
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
	}
}


int GetPresentAngle5(void)
{
	static int PresentAngle5;
	PresentAngle5=(float)stcAngle5.Angle[0]/32768*180;
	return PresentAngle5;
}