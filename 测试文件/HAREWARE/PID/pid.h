#ifndef _PID_H
#define _PID_H
#include"sys.h"
#include<stdio.h>
//struct strupid
//{
//	u16 SampleTime;
//}PID;

int PID_Operation(u8 sv,int pv,float kp,float ki,float kd);

#endif