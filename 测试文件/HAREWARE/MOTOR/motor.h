#ifndef _MOTOR_H
#define _MOTOR_H
#include"sys.h"

#define Direction_Value_LeftHip PFout(14)  //TargetValue.Direction_Value_LeftHip   FIR1 PFout(14)
#define Direction_Value_LeftKnee PFout(0)
#define Direction_Value_RightHip PFout(1)
#define Direction_Value_RightKnee PFout(13)

#define PA6 PAout(6)
#define PA7 PAout(7) 
#define PB0 PBout(0) 
#define PB1 PBout(1) 

void Motor_GPIO_Init(void);

//#define EN1 PGout(4)
//#define FR1 PGout(5)
//#define EN2 PGout(0)
//#define FR2 PGout(1)
//#define FR3 PFout(1)
//#define BK3 PFout(2)
//#define PUS1 PFout(13)
//#define BK1 PGout(8)
//#define BK2 PGout(9)

#endif