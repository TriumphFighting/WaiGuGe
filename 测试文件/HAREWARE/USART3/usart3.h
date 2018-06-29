#ifndef _USART3_H
#define _USART3_H

#include"sys.h"

void USART3_InterRupt_Init(void);
int GetPresentAngle3(void);

struct STime3
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc3
{
	short a[3];
	short T;
};
struct SGyro3
{
	short w[3];
	short T;
};
struct SAngle3
{
	short Angle[3];
	short T;
};
struct SMag3
{
	short h[3];
	short T;
};

struct SDStatus3
{
	short sDStatus[4];
};

struct SPress3
{
	long lPressure;
	long lAltitude;
};

struct SLonLat3
{
	long lLon;
	long lLat;
};

struct SGPSV3
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};

#endif