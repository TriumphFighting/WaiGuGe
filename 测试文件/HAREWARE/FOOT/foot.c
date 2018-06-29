#include"foot.h"
#include"delay.h"
#include"motor.h"
#include"led.h"
#include"key.h"
#include"usart1.h"
#include"usart3.h"
#include"usart4.h"
#include"usart5.h"
#include <stdio.h>
#include<math.h>

/********************************��ʱ������**************************************/
#define ArrayLength 6
char str[300];

extern u16 ToggleTime_axis1;//��1
extern u32 PulseCounter_axis1;
extern u16 ToggleTime_axis2;//��2
extern u32 PulseCounter_axis2;
extern u16 ToggleTime_axis3;//��3
extern u32 PulseCounter_axis3;
extern u16 ToggleTime_axis4;//��4
extern u32 PulseCounter_axis4;
/********************************0.���尴��**************************************/
u8 Up_Flag; 
u8 Go_Flag; 
u8 Down_Flag; 
u8 Stop_Flag;
/********************************1.����ṹ�����**************************************/
AimVal TargetValue;
/********************************2.����Ƕ�**************************************/
u16 Angle_Left_Hip_Array[ArrayLength];
u16 Angle_Left_Knee_Array[ArrayLength];
u16 Angle_Right_Hip_Array[ArrayLength];
u16 Angle_Right_Knee_Array[ArrayLength];

u16 Angle_Up_Left_Hip_Array[ArrayLength]={13,103};//����
u16 Angle_Up_Left_Knee_Array[ArrayLength]={13,103};
u16 Angle_Up_Right_Hip_Array[ArrayLength]={13,103};
u16 Angle_Up_Right_Knee_Array[ArrayLength]={13,103};

int Angle_Go_Left_Hip_Array[ArrayLength];//={0,-9,-14,31,18,-6,-9,28,14,-6,-9,28,14,0}; //��        {0,-6,-10,-9,-2,19,17,19,0}
int Angle_Go_Left_Knee_Array[ArrayLength];//={0,-19,-23,-24,9,-12,-17,-33,12,-12,-17,-33,12,0};
int Angle_Go_Right_Hip_Array[ArrayLength];//={0,44,21,-5,-5,37,17,-7,-9,37,17,-7,-9,0};
int Angle_Go_Right_Knee_Array[ArrayLength];//={0,-34,11,-12,-19,-30,11,-16,-21,-30,11,-16,-21,0};

u16 Angle_Down_Left_Hip_Array[ArrayLength]={110,20};//����
u16 Angle_Down_Left_Knee_Array[ArrayLength]={90};
u16 Angle_Down_Right_Hip_Array[ArrayLength]={110,20};
u16 Angle_Down_Right_Knee_Array[ArrayLength]={90};

u16 Angle_GoHome_Left_Hip_Array[ArrayLength];//��ԭ��
u16 Angle_GoHome_Left_Knee_Array[ArrayLength];
u16 Angle_GoHome_Right_Hip_Array[ArrayLength];
u16 Angle_GoHome_Right_Knee_Array[ArrayLength];

/********************************3.�����ٶ�**************************************/
u16 Speed_Left_Hip_Array[ArrayLength];
u16 Speed_Left_Knee_Array[ArrayLength];
u16 Speed_Right_Hip_Array[ArrayLength];
u16 Speed_Right_Knee_Array[ArrayLength];

u16 Speed_Up_Left_Hip_Array[ArrayLength]={100,200};  //��λΪ��10��/s)
u16 Speed_Up_Left_Knee_Array[ArrayLength]={100,200};
u16 Speed_Up_Right_Hip_Array[ArrayLength]={100,200};
u16 Speed_Up_Right_Knee_Array[ArrayLength]={100,200};

u16 Speed_Go_Left_Hip_Array[ArrayLength]={121,162,203};//��
u16 Speed_Go_Left_Knee_Array[ArrayLength]={291,240,191};
u16 Speed_Go_Right_Hip_Array[ArrayLength]={194,156,119};
u16 Speed_Go_Right_Knee_Array[ArrayLength]={194,240,287};

u16 Speed_Down_Left_Hip_Array[ArrayLength]={220,200};//����
u16 Speed_Down_Left_Knee_Array[ArrayLength]={180};
u16 Speed_Down_Right_Hip_Array[ArrayLength]={220,200};
u16 Speed_Down_Right_Knee_Array[ArrayLength]={180};

u16 Speed_GoHome_Left_Hip_Array[ArrayLength]={100};//��ԭ��
u16 Speed_GoHome_Left_Knee_Array[ArrayLength]={100};
u16 Speed_GoHome_Right_Hip_Array[ArrayLength]={100};
u16 Speed_GoHome_Right_Knee_Array[ArrayLength]={100};

/********************************4.���巽��**************************************/
u8 Direction_Left_Hip_Array[ArrayLength];
u8 Direction_Left_Knee_Array[ArrayLength];
u8 Direction_Right_Hip_Array[ArrayLength];
u8 Direction_Right_Knee_Array[ArrayLength];

u8 Direction_Up_Left_Hip_Array[ArrayLength]={0,1};//����
u8 Direction_Up_Left_Knee_Array[ArrayLength]={1,0};
u8 Direction_Up_Right_Hip_Array[ArrayLength]={1,0};
u8 Direction_Up_Right_Knee_Array[ArrayLength]={0,1};

u8 Direction_Go_Left_Hip_Array[ArrayLength];//��
u8 Direction_Go_Left_Knee_Array[ArrayLength];
u8 Direction_Go_Right_Hip_Array[ArrayLength];
u8 Direction_Go_Right_Knee_Array[ArrayLength];

u8 Direction_Down_Left_Hip_Array[ArrayLength]={0,1};//����
u8 Direction_Down_Left_Knee_Array[ArrayLength]={1};
u8 Direction_Down_Right_Hip_Array[ArrayLength]={1,0};
u8 Direction_Down_Right_Knee_Array[ArrayLength]={0};

u8 Direction_GoHome_Left_Hip_Array[ArrayLength];//��ԭ��
u8 Direction_GoHome_Left_Knee_Array[ArrayLength];
u8 Direction_GoHome_Right_Hip_Array[ArrayLength];
u8 Direction_GoHome_Right_Knee_Array[ArrayLength];

/********************************5.�����˶�״̬**************************************/
void UpConfig(void)
{
	u8 i;
	for(i=0;i<ArrayLength;i++)
	{
		Angle_Left_Hip_Array[i]=Angle_Up_Left_Hip_Array[i];//�Ƕ�
		Angle_Left_Knee_Array[i]=Angle_Up_Left_Knee_Array[i];
		Angle_Right_Hip_Array[i]=Angle_Up_Right_Hip_Array[i];
		Angle_Right_Knee_Array[i]=Angle_Up_Right_Knee_Array[i];
		
		Speed_Left_Hip_Array[i]=Speed_Up_Left_Hip_Array[i];//�ٶ�
		Speed_Left_Knee_Array[i]=Speed_Up_Left_Knee_Array[i];
		Speed_Right_Hip_Array[i]=Speed_Up_Right_Hip_Array[i];
		Speed_Right_Knee_Array[i]=Speed_Up_Right_Knee_Array[i];
		
		Direction_Left_Hip_Array[i]=Direction_Up_Left_Hip_Array[i];//����
		Direction_Left_Knee_Array[i]=Direction_Up_Left_Knee_Array[i];
		Direction_Right_Hip_Array[i]=Direction_Up_Right_Hip_Array[i];
		Direction_Right_Knee_Array[i]=Direction_Up_Right_Knee_Array[i];
	}
}

void GoConfig(void)
{
	u8 i;
	for(i=0;i<ArrayLength;i++)
	{
		Angle_Left_Hip_Array[i]=Angle_Go_Left_Hip_Array[i];//�Ƕ�
		Angle_Left_Knee_Array[i]=Angle_Go_Left_Knee_Array[i];
		Angle_Right_Hip_Array[i]=Angle_Go_Right_Hip_Array[i];
		Angle_Right_Knee_Array[i]=Angle_Go_Right_Knee_Array[i];
		
		Speed_Left_Hip_Array[i]=Speed_Go_Left_Hip_Array[i];//�ٶ�
		Speed_Left_Knee_Array[i]=Speed_Go_Left_Knee_Array[i];
		Speed_Right_Hip_Array[i]=Speed_Go_Right_Hip_Array[i];
		Speed_Right_Knee_Array[i]=Speed_Go_Right_Knee_Array[i];
		
		Direction_Left_Hip_Array[i]=Direction_Go_Left_Hip_Array[i];//����
		Direction_Left_Knee_Array[i]=Direction_Go_Left_Knee_Array[i];
		Direction_Right_Hip_Array[i]=Direction_Go_Right_Hip_Array[i];
		Direction_Right_Knee_Array[i]=Direction_Go_Right_Knee_Array[i];
	}
}

void DownConfig(void)
{
	u8 i;
	for(i=0;i<ArrayLength;i++)
	{
		Angle_Left_Hip_Array[i]=Angle_Down_Left_Hip_Array[i];//�Ƕ�
		Angle_Left_Knee_Array[i]=Angle_Down_Left_Knee_Array[i];
		Angle_Right_Hip_Array[i]=Angle_Down_Right_Hip_Array[i];
		Angle_Right_Knee_Array[i]=Angle_Down_Right_Knee_Array[i];
		
		Speed_Left_Hip_Array[i]=Speed_Down_Left_Hip_Array[i];//�ٶ�
		Speed_Left_Knee_Array[i]=Speed_Down_Left_Knee_Array[i];
		Speed_Right_Hip_Array[i]=Speed_Down_Right_Hip_Array[i];
		Speed_Right_Knee_Array[i]=Speed_Down_Right_Knee_Array[i];
		
		Direction_Left_Hip_Array[i]=Direction_Down_Left_Hip_Array[i];//����
		Direction_Left_Knee_Array[i]=Direction_Down_Left_Knee_Array[i];
		Direction_Right_Hip_Array[i]=Direction_Down_Right_Hip_Array[i];
		Direction_Right_Knee_Array[i]=Direction_Down_Right_Knee_Array[i];
	}
}

void GoHomeConfig(void)
{
	u8 i;
	for(i=0;i<ArrayLength;i++)
	{
		Angle_Left_Hip_Array[i]=Angle_GoHome_Left_Hip_Array[i];//�Ƕ�
		Angle_Left_Knee_Array[i]=Angle_GoHome_Left_Knee_Array[i];
		Angle_Right_Hip_Array[i]=Angle_GoHome_Right_Hip_Array[i];
		Angle_Right_Knee_Array[i]=Angle_GoHome_Right_Knee_Array[i];
		
		Speed_Left_Hip_Array[i]=Speed_GoHome_Left_Hip_Array[i];//�ٶ�
		Speed_Left_Knee_Array[i]=Speed_GoHome_Left_Knee_Array[i];
		Speed_Right_Hip_Array[i]=Speed_GoHome_Right_Hip_Array[i];
		Speed_Right_Knee_Array[i]=Speed_GoHome_Right_Knee_Array[i];
		
		Direction_Left_Hip_Array[i]=Direction_GoHome_Left_Hip_Array[i];//����
		Direction_Left_Knee_Array[i]=Direction_GoHome_Left_Knee_Array[i];
		Direction_Right_Hip_Array[i]=Direction_GoHome_Right_Hip_Array[i];
		Direction_Right_Knee_Array[i]=Direction_GoHome_Right_Knee_Array[i];
	}
}

/********************************6.��������&�Ƕ�ת��**************************************/

u32 Angel_To_PUL(u16 PPR,u8 Ratio,u16 Angel)
{
	u32 Pulse;
	double k0;
	k0=PPR*2*Ratio*Angel/360.0;
	Pulse=k0+0.5;
	return(Pulse);
}

/********************************7.����Ƶ��&�ٶ�ת��**************************************/

u32 Speed_To_Frequency(u16 PPR,u8 Ratio,u16 Speed)//Speed��λΪ��10��/s)��TΪs
{
	u32 T;
	double k1,k2,k3;
	k1=PPR*Ratio*Speed;
	k2=18000000.0/k1;
	k3=k2*6*60*10;
	T=k3/2.0+0.5;
	return(T);
}
/*******************************8.���ᣨ�ŷ����������**************************************/
void FourAxisCarryOut(void)
{	
		u8 i;
		u8 Axis1;
		u8 Axis2;
		u8 Axis3;
		u8 Axis4;
		LED1=0;
		TIM_Cmd(TIM3, ENABLE);
		for(i=0;i<ArrayLength;i++)
		{				
				Direction_Value_LeftHip=Direction_Left_Hip_Array[i];//��1
				TargetValue.Angle_Value_LeftHip=Angle_Left_Hip_Array[i];
				TargetValue.Speed_Value_LeftHip=Speed_To_Frequency(2500,100,Speed_Left_Hip_Array[i]);
				ToggleTime_axis1=TargetValue.Speed_Value_LeftHip;
			
				Direction_Value_LeftKnee=Direction_Left_Knee_Array[i];//��2
				TargetValue.Angle_Value_LeftKnee=Angle_Left_Knee_Array[i];
				TargetValue.Speed_Value_LeftKnee=Speed_To_Frequency(2500,100,Speed_Left_Knee_Array[i]);
				ToggleTime_axis2=TargetValue.Speed_Value_LeftKnee;
			
				Direction_Value_RightHip=Direction_Right_Hip_Array[i];//��3
				TargetValue.Angle_Value_RightHip=Angle_Right_Hip_Array[i];
				TargetValue.Speed_Value_RightHip=Speed_To_Frequency(2500,100,Speed_Right_Hip_Array[i]);
				ToggleTime_axis3=TargetValue.Speed_Value_RightHip;
			
				Direction_Value_RightKnee=Direction_Right_Knee_Array[i];//��4
				TargetValue.Angle_Value_RightKnee=Angle_Right_Knee_Array[i];
				TargetValue.Speed_Value_RightKnee=Speed_To_Frequency(2500,100,Speed_Right_Knee_Array[i]);
				ToggleTime_axis4=TargetValue.Speed_Value_RightKnee;
			
				/***************************************��ӡ************************************/
//			  sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//			  TargetValue.Angle_Value_LeftHip,Speed_Left_Hip_Array[i],Direction_Left_Hip_Array[i],\
//			  TargetValue.Angle_Value_LeftKnee,Speed_Left_Knee_Array[i],Direction_Left_Knee_Array[i],\
//			  TargetValue.Angle_Value_RightHip,Speed_Right_Hip_Array[i],Direction_Right_Hip_Array[i],\
//				TargetValue.Angle_Value_RightKnee,Speed_Right_Knee_Array[i],Direction_Right_Knee_Array[i]);
//  	  	UART1_Put_String(str);		//��ӡ		
				/***************************************��ӡ************************************/
			
				TIM_ITConfig(TIM3,TIM_IT_CC1,ENABLE); //��1 
				TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE); //��2
				TIM_ITConfig(TIM3,TIM_IT_CC3,ENABLE); //��3 
				TIM_ITConfig(TIM3,TIM_IT_CC4,ENABLE); //��4 
				while(1)
				{
						if(PulseCounter_axis1>=Angel_To_PUL(2500,100,TargetValue.Angle_Value_LeftHip))//��1                     Angel_To_PUL(u16 PPR,u8 Ratio,u16 Angel)2500*2*50*Angle/360
						{				
							TIM_ITConfig(TIM3,TIM_IT_CC1,DISABLE); 
							PulseCounter_axis1=0;
							Axis1=1;
						}
						if(PulseCounter_axis2>=Angel_To_PUL(2500,100,TargetValue.Angle_Value_LeftKnee))//��2                                               6400*2*60*Angle_2/360
						{	
							TIM_ITConfig(TIM3,TIM_IT_CC2,DISABLE); 
							PulseCounter_axis2=0;
							Axis2=1;
						}
						if(PulseCounter_axis3>=Angel_To_PUL(2500,100,TargetValue.Angle_Value_RightHip))//��3                                               6400*2*60*Angle_2/360
						{	
							TIM_ITConfig(TIM3,TIM_IT_CC3,DISABLE); 
							PulseCounter_axis3=0;
							Axis3=1;
						}
						if(PulseCounter_axis4>=Angel_To_PUL(2500,100,TargetValue.Angle_Value_RightKnee))//��4                                               6400*2*60*Angle_2/360
						{	
							TIM_ITConfig(TIM3,TIM_IT_CC4,DISABLE); 
							PulseCounter_axis4=0;
							Axis4=1;
						}
						if(Axis1==1&&Axis2==1&&Axis3==1&&Axis4==1)
						{
							Axis1=0;
							Axis2=0;
							Axis3=0;
							Axis4=0;
							delay_ms(10);
							break;
						}
				}
		}
		TIM_Cmd(TIM3,DISABLE);
		LED1=1;
}
/*******************************9.���߽Ƕ��ٶȻ��㹫ʽ**************************************/
void BowConfig(void)//����
{	
	#define BowLength 2
	u8 i,j;
	float average;
	int Angle_Bow_Left_Hip_Array[BowLength]={0,13};
	int Angle_Bow_Left_Knee_Array[BowLength]={0,3};
	int Angle_Bow_Right_Hip_Array[BowLength]={0,13};
	int Angle_Bow_Right_Knee_Array[BowLength]={0,3}; 
	for(j=0;j<ArrayLength;j++)//����
	{
		Angle_Go_Left_Hip_Array[j]=0;
		Angle_Go_Left_Knee_Array[j]=0;
		Angle_Go_Right_Hip_Array[j]=0;
		Angle_Go_Right_Knee_Array[j]=0;	
		
		Speed_Go_Left_Hip_Array[j]=0;
		Speed_Go_Left_Knee_Array[j]=0;
		Speed_Go_Right_Hip_Array[j]=0;
		Speed_Go_Right_Knee_Array[j]=0;	
		
		Direction_Go_Left_Hip_Array[j]=0;
		Direction_Go_Left_Knee_Array[j]=0;
		Direction_Go_Right_Hip_Array[j]=0;
		Direction_Go_Right_Knee_Array[j]=0;
	}
	for(i=0;i<BowLength-1;i++)
	{
		//�Ƕ�
		Angle_Go_Left_Hip_Array[i]=Angle_Bow_Left_Hip_Array[i+1]-Angle_Bow_Left_Hip_Array[i];
		Angle_Go_Left_Knee_Array[i]=Angle_Bow_Left_Knee_Array[i+1]-Angle_Bow_Left_Knee_Array[i];
		Angle_Go_Right_Hip_Array[i]=Angle_Bow_Right_Hip_Array[i+1]-Angle_Bow_Right_Hip_Array[i];
		Angle_Go_Right_Knee_Array[i]=Angle_Bow_Right_Knee_Array[i+1]-Angle_Bow_Right_Knee_Array[i];
		//����
		if(Angle_Go_Left_Hip_Array[i]<0){Direction_Go_Left_Hip_Array[i]=1;Angle_Go_Left_Hip_Array[i]=-Angle_Go_Left_Hip_Array[i];}
		if(Angle_Go_Left_Knee_Array[i]<0){Direction_Go_Left_Knee_Array[i]=1;Angle_Go_Left_Knee_Array[i]=-Angle_Go_Left_Knee_Array[i];}
		if(Angle_Go_Right_Hip_Array[i]>0)Direction_Go_Right_Hip_Array[i]=1;else Angle_Go_Right_Hip_Array[i]=-Angle_Go_Right_Hip_Array[i];
		if(Angle_Go_Right_Knee_Array[i]>0)Direction_Go_Right_Knee_Array[i]=1;else Angle_Go_Right_Knee_Array[i]=-Angle_Go_Right_Knee_Array[i];
		//�ٶ�
		average=(Angle_Go_Left_Hip_Array[i]+Angle_Go_Left_Knee_Array[i]+Angle_Go_Right_Hip_Array[i]+Angle_Go_Right_Knee_Array[i])/4;
		Speed_Go_Left_Hip_Array[i]=(float)150*Angle_Go_Left_Hip_Array[i]/average;
		Speed_Go_Left_Knee_Array[i]=(float)150*Angle_Go_Left_Knee_Array[i]/average;
		Speed_Go_Right_Hip_Array[i]=(float)150*Angle_Go_Right_Hip_Array[i]/average;
		Speed_Go_Right_Knee_Array[i]=(float)150*Angle_Go_Right_Knee_Array[i]/average;
		//��ӡ 
//		sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//		Angle_Go_Left_Hip_Array[i],Speed_Go_Left_Hip_Array[i],Direction_Go_Left_Hip_Array[i],\
//		Angle_Go_Left_Knee_Array[i],Speed_Go_Left_Knee_Array[i],Direction_Go_Left_Knee_Array[i],\
//		Angle_Go_Right_Hip_Array[i],Speed_Go_Right_Hip_Array[i],Direction_Go_Right_Hip_Array[i],\
//		Angle_Go_Right_Knee_Array[i],Speed_Go_Right_Knee_Array[i],Direction_Go_Right_Knee_Array[i]);
//		UART1_Put_String(str);	
//		delay_ms(50);
	}
}


void RaiseLegConfig(void)//̧��
{
	u8 i,j;
	float average;
	int Angle_RaiseLeg_Left_Hip_Array[2]={-7,-10};
	int Angle_RaiseLeg_Left_Knee_Array[2]={-14,-19};
	int Angle_RaiseLeg_Right_Hip_Array[2]={39,18};
	int Angle_RaiseLeg_Right_Knee_Array[2]={-31,11};	
	for(j=0;j<ArrayLength;j++)//����
	{
		Angle_Go_Left_Hip_Array[j]=0;
		Angle_Go_Left_Knee_Array[j]=0;
		Angle_Go_Right_Hip_Array[j]=0;
		Angle_Go_Right_Knee_Array[j]=0;	
		
		Speed_Go_Left_Hip_Array[j]=0;
		Speed_Go_Left_Knee_Array[j]=0;
		Speed_Go_Right_Hip_Array[j]=0;
		Speed_Go_Right_Knee_Array[j]=0;	
		
		Direction_Go_Left_Hip_Array[j]=0;
		Direction_Go_Left_Knee_Array[j]=0;
		Direction_Go_Right_Hip_Array[j]=0;
		Direction_Go_Right_Knee_Array[j]=0;
	}
	//�Ƕ�
	Angle_Go_Left_Hip_Array[0]=Angle_RaiseLeg_Left_Hip_Array[0];
	Angle_Go_Left_Knee_Array[0]=Angle_RaiseLeg_Left_Knee_Array[0];
	Angle_Go_Right_Hip_Array[0]=Angle_RaiseLeg_Right_Hip_Array[0];
	Angle_Go_Right_Knee_Array[0]=Angle_RaiseLeg_Right_Knee_Array[0];
	
	Angle_Go_Left_Hip_Array[1]=Angle_RaiseLeg_Left_Hip_Array[1]-Angle_RaiseLeg_Left_Hip_Array[0];
	Angle_Go_Left_Knee_Array[1]=Angle_RaiseLeg_Left_Knee_Array[1]-Angle_RaiseLeg_Left_Knee_Array[0];
	Angle_Go_Right_Hip_Array[1]=Angle_RaiseLeg_Right_Hip_Array[1]-Angle_RaiseLeg_Right_Hip_Array[0];
	Angle_Go_Right_Knee_Array[1]=Angle_RaiseLeg_Right_Knee_Array[1]-Angle_RaiseLeg_Right_Knee_Array[0];	
	for(i=0;i<2;i++)
	{
		 //����
		 if(Angle_Go_Left_Hip_Array[i]<0){Direction_Go_Left_Hip_Array[i]=1;Angle_Go_Left_Hip_Array[i]=-Angle_Go_Left_Hip_Array[i];}
		 if(Angle_Go_Left_Knee_Array[i]<0){Direction_Go_Left_Knee_Array[i]=1;Angle_Go_Left_Knee_Array[i]=-Angle_Go_Left_Knee_Array[i];}
		 if(Angle_Go_Right_Hip_Array[i]>0)Direction_Go_Right_Hip_Array[i]=1;else Angle_Go_Right_Hip_Array[i]=-Angle_Go_Right_Hip_Array[i];
		 if(Angle_Go_Right_Knee_Array[i]>0)Direction_Go_Right_Knee_Array[i]=1;else Angle_Go_Right_Knee_Array[i]=-Angle_Go_Right_Knee_Array[i];
		 //�ٶ�
		 average=(Angle_Go_Left_Hip_Array[i]+Angle_Go_Left_Knee_Array[i]+Angle_Go_Right_Hip_Array[i]+Angle_Go_Right_Knee_Array[i])/4;
		 Speed_Go_Left_Hip_Array[i]=(float)150*Angle_Go_Left_Hip_Array[i]/average;
		 Speed_Go_Left_Knee_Array[i]=(float)150*Angle_Go_Left_Knee_Array[i]/average;
		 Speed_Go_Right_Hip_Array[i]=(float)150*Angle_Go_Right_Hip_Array[i]/average;
		 Speed_Go_Right_Knee_Array[i]=(float)150*Angle_Go_Right_Knee_Array[i]/average;
		 //��ӡ
//		 sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//		 Angle_Go_Left_Hip_Array[i],Speed_Go_Left_Hip_Array[i],Direction_Go_Left_Hip_Array[i],\
//		 Angle_Go_Left_Knee_Array[i],Speed_Go_Left_Knee_Array[i],Direction_Go_Left_Knee_Array[i],\
//		 Angle_Go_Right_Hip_Array[i],Speed_Go_Right_Hip_Array[i],Direction_Go_Right_Hip_Array[i],\
//		 Angle_Go_Right_Knee_Array[i],Speed_Go_Right_Knee_Array[i],Direction_Go_Right_Knee_Array[i]);
//		 UART1_Put_String(str);	
//		 delay_ms(50);
	}	
}


void WalkCycleConfig(void)//ѭ����
{
	#define WALKLENGTH 5
	u8 i,j;
	float average;
	int Angle_WalkCycle_Left_Hip_Array[WALKLENGTH]={-10,29,15,-7,-10};
	int Angle_WalkCycle_Left_Knee_Array[WALKLENGTH]={-19,-30,11,-14,-19};
	int Angle_WalkCycle_Right_Hip_Array[WALKLENGTH]={18,-6,-8,39,18};
	int Angle_WalkCycle_Right_Knee_Array[WALKLENGTH]={11,-14,-20,-31,11}; 
	for(j=0;j<ArrayLength;j++)//����
	{
		Angle_Go_Left_Hip_Array[j]=0;
		Angle_Go_Left_Knee_Array[j]=0;
		Angle_Go_Right_Hip_Array[j]=0;
		Angle_Go_Right_Knee_Array[j]=0;	
		
		Speed_Go_Left_Hip_Array[j]=0;
		Speed_Go_Left_Knee_Array[j]=0;
		Speed_Go_Right_Hip_Array[j]=0;
		Speed_Go_Right_Knee_Array[j]=0;	
		
		Direction_Go_Left_Hip_Array[j]=0;
		Direction_Go_Left_Knee_Array[j]=0;
		Direction_Go_Right_Hip_Array[j]=0;
		Direction_Go_Right_Knee_Array[j]=0;
	}
	for(i=0;i<WALKLENGTH-1;i++)
	{
		//�Ƕ�
		Angle_Go_Left_Hip_Array[i]=Angle_WalkCycle_Left_Hip_Array[i+1]-Angle_WalkCycle_Left_Hip_Array[i];
		Angle_Go_Left_Knee_Array[i]=Angle_WalkCycle_Left_Knee_Array[i+1]-Angle_WalkCycle_Left_Knee_Array[i];
		Angle_Go_Right_Hip_Array[i]=Angle_WalkCycle_Right_Hip_Array[i+1]-Angle_WalkCycle_Right_Hip_Array[i];
		Angle_Go_Right_Knee_Array[i]=Angle_WalkCycle_Right_Knee_Array[i+1]-Angle_WalkCycle_Right_Knee_Array[i];
		//����
		if(Angle_Go_Left_Hip_Array[i]<0){Direction_Go_Left_Hip_Array[i]=1;Angle_Go_Left_Hip_Array[i]=-Angle_Go_Left_Hip_Array[i];}
		if(Angle_Go_Left_Knee_Array[i]<0){Direction_Go_Left_Knee_Array[i]=1;Angle_Go_Left_Knee_Array[i]=-Angle_Go_Left_Knee_Array[i];}
		if(Angle_Go_Right_Hip_Array[i]>0)Direction_Go_Right_Hip_Array[i]=1;else Angle_Go_Right_Hip_Array[i]=-Angle_Go_Right_Hip_Array[i];
		if(Angle_Go_Right_Knee_Array[i]>0)Direction_Go_Right_Knee_Array[i]=1;else Angle_Go_Right_Knee_Array[i]=-Angle_Go_Right_Knee_Array[i];
		//�ٶ�
		average=(Angle_Go_Left_Hip_Array[i]+Angle_Go_Left_Knee_Array[i]+Angle_Go_Right_Hip_Array[i]+Angle_Go_Right_Knee_Array[i])/4;
		Speed_Go_Left_Hip_Array[i]=(float)150*Angle_Go_Left_Hip_Array[i]/average;
		Speed_Go_Left_Knee_Array[i]=(float)150*Angle_Go_Left_Knee_Array[i]/average;
		Speed_Go_Right_Hip_Array[i]=(float)150*Angle_Go_Right_Hip_Array[i]/average;
		Speed_Go_Right_Knee_Array[i]=(float)150*Angle_Go_Right_Knee_Array[i]/average;
		//��ӡ 
//		sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//		Angle_Go_Left_Hip_Array[i],Speed_Go_Left_Hip_Array[i],Direction_Go_Left_Hip_Array[i],\
//		Angle_Go_Left_Knee_Array[i],Speed_Go_Left_Knee_Array[i],Direction_Go_Left_Knee_Array[i],\
//		Angle_Go_Right_Hip_Array[i],Speed_Go_Right_Hip_Array[i],Direction_Go_Right_Hip_Array[i],\
//		Angle_Go_Right_Knee_Array[i],Speed_Go_Right_Knee_Array[i],Direction_Go_Right_Knee_Array[i]);
//		UART1_Put_String(str);	
//		delay_ms(50);
	}
}


void MergeLegConfig(void)//˫�Ȳ�£
{
	#define MergeLegLength 2
	u8 i,j;
	float average;
	int Angle_MergeLeg_Left_Hip_Array[MergeLegLength]={-10,0};
	int Angle_MergeLeg_Left_Knee_Array[MergeLegLength]={-19,0};
	int Angle_MergeLeg_Right_Hip_Array[MergeLegLength]={18,0};
	int Angle_MergeLeg_Right_Knee_Array[MergeLegLength]={11,0}; 
	for(j=0;j<ArrayLength;j++)//����
	{
		Angle_Go_Left_Hip_Array[j]=0;
		Angle_Go_Left_Knee_Array[j]=0;
		Angle_Go_Right_Hip_Array[j]=0;
		Angle_Go_Right_Knee_Array[j]=0;	
		
		Speed_Go_Left_Hip_Array[j]=0;
		Speed_Go_Left_Knee_Array[j]=0;
		Speed_Go_Right_Hip_Array[j]=0;
		Speed_Go_Right_Knee_Array[j]=0;	
		
		Direction_Go_Left_Hip_Array[j]=0;
		Direction_Go_Left_Knee_Array[j]=0;
		Direction_Go_Right_Hip_Array[j]=0;
		Direction_Go_Right_Knee_Array[j]=0;
	}
	for(i=0;i<MergeLegLength-1;i++)
	{
		//�Ƕ�
		Angle_Go_Left_Hip_Array[i]=Angle_MergeLeg_Left_Hip_Array[i+1]-Angle_MergeLeg_Left_Hip_Array[i];
		Angle_Go_Left_Knee_Array[i]=Angle_MergeLeg_Left_Knee_Array[i+1]-Angle_MergeLeg_Left_Knee_Array[i];
		Angle_Go_Right_Hip_Array[i]=Angle_MergeLeg_Right_Hip_Array[i+1]-Angle_MergeLeg_Right_Hip_Array[i];
		Angle_Go_Right_Knee_Array[i]=Angle_MergeLeg_Right_Knee_Array[i+1]-Angle_MergeLeg_Right_Knee_Array[i];
		//����
		if(Angle_Go_Left_Hip_Array[i]<0){Direction_Go_Left_Hip_Array[i]=1;Angle_Go_Left_Hip_Array[i]=-Angle_Go_Left_Hip_Array[i];}
		if(Angle_Go_Left_Knee_Array[i]<0){Direction_Go_Left_Knee_Array[i]=1;Angle_Go_Left_Knee_Array[i]=-Angle_Go_Left_Knee_Array[i];}
		if(Angle_Go_Right_Hip_Array[i]>0)Direction_Go_Right_Hip_Array[i]=1;else Angle_Go_Right_Hip_Array[i]=-Angle_Go_Right_Hip_Array[i];
		if(Angle_Go_Right_Knee_Array[i]>0)Direction_Go_Right_Knee_Array[i]=1;else Angle_Go_Right_Knee_Array[i]=-Angle_Go_Right_Knee_Array[i];
		//�ٶ�
		average=(Angle_Go_Left_Hip_Array[i]+Angle_Go_Left_Knee_Array[i]+Angle_Go_Right_Hip_Array[i]+Angle_Go_Right_Knee_Array[i])/4;
		Speed_Go_Left_Hip_Array[i]=(float)150*Angle_Go_Left_Hip_Array[i]/average;
		Speed_Go_Left_Knee_Array[i]=(float)150*Angle_Go_Left_Knee_Array[i]/average;
		Speed_Go_Right_Hip_Array[i]=(float)150*Angle_Go_Right_Hip_Array[i]/average;
		Speed_Go_Right_Knee_Array[i]=(float)150*Angle_Go_Right_Knee_Array[i]/average;
		//��ӡ 
//		sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//		Angle_Go_Left_Hip_Array[i],Speed_Go_Left_Hip_Array[i],Direction_Go_Left_Hip_Array[i],\
//		Angle_Go_Left_Knee_Array[i],Speed_Go_Left_Knee_Array[i],Direction_Go_Left_Knee_Array[i],\
//		Angle_Go_Right_Hip_Array[i],Speed_Go_Right_Hip_Array[i],Direction_Go_Right_Hip_Array[i],\
//		Angle_Go_Right_Knee_Array[i],Speed_Go_Right_Knee_Array[i],Direction_Go_Right_Knee_Array[i]);
//		UART1_Put_String(str);	
//		delay_ms(50);
	}
}


void UpRightLegConfig(void)//˫��ֱ��
{
	#define UpRightLegLength 2
	u8 i,j;
	float average;
	int Angle_UpRightLeg_Left_Hip_Array[UpRightLegLength]={13,0};
	int Angle_UpRightLeg_Left_Knee_Array[UpRightLegLength]={3,0};
	int Angle_UpRightLeg_Right_Hip_Array[UpRightLegLength]={13,0};
	int Angle_UpRightLeg_Right_Knee_Array[UpRightLegLength]={3,0}; 
	for(j=0;j<ArrayLength;j++)//����
	{
		Angle_Go_Left_Hip_Array[j]=0;
		Angle_Go_Left_Knee_Array[j]=0;
		Angle_Go_Right_Hip_Array[j]=0;
		Angle_Go_Right_Knee_Array[j]=0;	
		
		Speed_Go_Left_Hip_Array[j]=0;
		Speed_Go_Left_Knee_Array[j]=0;
		Speed_Go_Right_Hip_Array[j]=0;
		Speed_Go_Right_Knee_Array[j]=0;	
		
		Direction_Go_Left_Hip_Array[j]=0;
		Direction_Go_Left_Knee_Array[j]=0;
		Direction_Go_Right_Hip_Array[j]=0;
		Direction_Go_Right_Knee_Array[j]=0;
	}
	for(i=0;i<UpRightLegLength-1;i++)
	{
		//�Ƕ�
		Angle_Go_Left_Hip_Array[i]=Angle_UpRightLeg_Left_Hip_Array[i+1]-Angle_UpRightLeg_Left_Hip_Array[i];
		Angle_Go_Left_Knee_Array[i]=Angle_UpRightLeg_Left_Knee_Array[i+1]-Angle_UpRightLeg_Left_Knee_Array[i];
		Angle_Go_Right_Hip_Array[i]=Angle_UpRightLeg_Right_Hip_Array[i+1]-Angle_UpRightLeg_Right_Hip_Array[i];
		Angle_Go_Right_Knee_Array[i]=Angle_UpRightLeg_Right_Knee_Array[i+1]-Angle_UpRightLeg_Right_Knee_Array[i];
		//����
		if(Angle_Go_Left_Hip_Array[i]<0){Direction_Go_Left_Hip_Array[i]=1;Angle_Go_Left_Hip_Array[i]=-Angle_Go_Left_Hip_Array[i];}
		if(Angle_Go_Left_Knee_Array[i]<0){Direction_Go_Left_Knee_Array[i]=1;Angle_Go_Left_Knee_Array[i]=-Angle_Go_Left_Knee_Array[i];}
		if(Angle_Go_Right_Hip_Array[i]>0)Direction_Go_Right_Hip_Array[i]=1;else Angle_Go_Right_Hip_Array[i]=-Angle_Go_Right_Hip_Array[i];
		if(Angle_Go_Right_Knee_Array[i]>0)Direction_Go_Right_Knee_Array[i]=1;else Angle_Go_Right_Knee_Array[i]=-Angle_Go_Right_Knee_Array[i];
		//�ٶ�
		average=(Angle_Go_Left_Hip_Array[i]+Angle_Go_Left_Knee_Array[i]+Angle_Go_Right_Hip_Array[i]+Angle_Go_Right_Knee_Array[i])/4;
		Speed_Go_Left_Hip_Array[i]=(float)150*Angle_Go_Left_Hip_Array[i]/average;
		Speed_Go_Left_Knee_Array[i]=(float)150*Angle_Go_Left_Knee_Array[i]/average;
		Speed_Go_Right_Hip_Array[i]=(float)150*Angle_Go_Right_Hip_Array[i]/average;
		Speed_Go_Right_Knee_Array[i]=(float)150*Angle_Go_Right_Knee_Array[i]/average;
		//��ӡ 
//		sprintf(str,"��%d��\r\n���ţ�1�ᣩ:�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��2��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n���ţ�3��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n��ϥ��4��):�Ƕȣ�%d���ٶȣ�%d������%d��\r\n\r\n",i,       
//		Angle_Go_Left_Hip_Array[i],Speed_Go_Left_Hip_Array[i],Direction_Go_Left_Hip_Array[i],\
//		Angle_Go_Left_Knee_Array[i],Speed_Go_Left_Knee_Array[i],Direction_Go_Left_Knee_Array[i],\
//		Angle_Go_Right_Hip_Array[i],Speed_Go_Right_Hip_Array[i],Direction_Go_Right_Hip_Array[i],\
//		Angle_Go_Right_Knee_Array[i],Speed_Go_Right_Knee_Array[i],Direction_Go_Right_Knee_Array[i]);
//		UART1_Put_String(str);	
//		delay_ms(50);
	}
}

void HipGoHomeInit(void)//�Ż�ԭ��
{
	int Err_Left_Hip;
	int Err_Right_Hip;
	//ϥ�ؽڲ���
	Angle_GoHome_Left_Knee_Array[0]=0;
	Angle_GoHome_Right_Knee_Array[0]=0;
	//����
	Err_Left_Hip=90-GetPresentAngle4();
	if(Err_Left_Hip>0) Direction_GoHome_Left_Hip_Array[0]=0;
	else {Direction_GoHome_Left_Hip_Array[0]=1;Err_Left_Hip=-Err_Left_Hip;}
	Angle_GoHome_Left_Hip_Array[0]=Err_Left_Hip;
	//��ӡ
//	sprintf(str,"����4��ǰ�Ƕȣ�%d\r\n�Ƕ�ƫ�%d\r\nӦת�Ƕȣ�%d\r\nӦת����%d\r\n\r\n",
//	GetPresentAngle4(),Err_Left_Hip,Angle_GoHome_Left_Hip_Array[0],Direction_GoHome_Left_Hip_Array[0]);
//	UART1_Put_String(str);
//	delay_ms(50);
	//����
	Err_Right_Hip=90-GetPresentAngle3();
	if(Err_Right_Hip>0) Direction_GoHome_Right_Hip_Array[0]=0;
	else {Direction_GoHome_Right_Hip_Array[0]=1;Err_Right_Hip=-Err_Right_Hip;}
	Angle_GoHome_Right_Hip_Array[0]=Err_Right_Hip;
	//��ӡ
//	sprintf(str,"����3��ǰ�Ƕȣ�%d\r\n�Ƕ�ƫ�%d\r\nӦת�Ƕȣ�%d\r\nӦת����%d\r\n\r\n",
//	GetPresentAngle3(),Err_Right_Hip,Angle_GoHome_Right_Hip_Array[0],Direction_GoHome_Right_Hip_Array[0]);
//	UART1_Put_String(str);
//	delay_ms(50);
}

void KneeGoHomeInit(void)//ϥ��ԭ��
{
	int Err_Left_Knee;
	int Err_Right_Knee;
	//�Źؽڲ���
	Angle_GoHome_Left_Hip_Array[0]=0;
	Angle_GoHome_Right_Hip_Array[0]=0;
	//��ϥ
	Err_Left_Knee=90-GetPresentAngle5();//��ϥ
	if(Err_Left_Knee>0) {Direction_GoHome_Left_Knee_Array[0]=0;}
	else {Direction_GoHome_Left_Knee_Array[0]=1;Err_Left_Knee=-Err_Left_Knee;}
	Angle_GoHome_Left_Knee_Array[0]=Err_Left_Knee;
	//��ӡ
//	sprintf(str,"����5��ǰ�Ƕȣ�%d\r\n�Ƕ�ƫ�%d\r\nӦת�Ƕȣ�%d\r\nӦת����%d\r\n\r\n",
//	GetPresentAngle5(),Err_Left_Knee,Angle_GoHome_Left_Knee_Array[0],Direction_GoHome_Left_Knee_Array[0]);
//	UART1_Put_String(str);
//	delay_ms(50);
	//��ϥ
	Err_Right_Knee=90-GetPresentAngle1();
	if(Err_Right_Knee>0) {Direction_GoHome_Right_Knee_Array[0]=0;}
	else {Direction_GoHome_Right_Knee_Array[0]=1;Err_Right_Knee=-Err_Right_Knee;}
	Angle_GoHome_Right_Knee_Array[0]=Err_Right_Knee;
	//��ӡ
//	sprintf(str,"����5��ǰ�Ƕȣ�%d\r\n�Ƕ�ƫ�%d\r\nӦת�Ƕȣ�%d\r\nӦת����%d\r\n\r\n",
//	GetPresentAngle5(),Err_Left_Knee,Angle_GoHome_Left_Knee_Array[0],Direction_GoHome_Left_Knee_Array[0]);
//	UART1_Put_String(str);
//	delay_ms(50);
}

void AutoGoHome(void)
{
	//�Ż�ԭ��
	HipGoHomeInit();
	GoHomeConfig();
	FourAxisCarryOut();
	//ϥ��ԭ��
	KneeGoHomeInit();
	GoHomeConfig();
	FourAxisCarryOut();
}