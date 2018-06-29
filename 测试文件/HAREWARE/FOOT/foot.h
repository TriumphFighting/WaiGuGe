#ifndef _FOOT_H
#define _FOOT_H
#include"sys.h"

typedef struct aimsval
{	
	u16 Angle_Value_LeftHip;//角度
	u16 Angle_Value_LeftKnee;
	u16 Angle_Value_RightHip;
	u16 Angle_Value_RightKnee;
	u16 Speed_Value_LeftHip;//速度
	u16 Speed_Value_LeftKnee;
	u16 Speed_Value_RightHip;
	u16 Speed_Value_RightKnee;
//	u16 Direction_Value_LeftHip;//方向
//	u16 Direction_Value_LeftKnee;
//	u16 Direction_Value_RightHip;
//	u16 Direction_Value_RightKnee;
}AimVal;

void AutoGoHome(void);
void UpConfig(void);
void GoConfig(void);
void DownConfig(void);
void FourAxisCarryOut(void);

void BowConfig(void);
void RaiseLegConfig(void);
void WalkCycleConfig(void);
void MergeLegConfig(void);
void UpRightLegConfig(void);
#endif
