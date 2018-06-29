#ifndef _USART5_
#define _USART5_
#include"sys.h"

void USART5_InterRupt_Init(void);
int GetPresentAngle5(void);

struct STime5
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc5
{
	short a[3];
	short T;
};
struct SGyro5
{
	short w[3];
	short T;
};
struct SAngle5
{
	short Angle[3];
	short T;
};
struct SMag5
{
	short h[3];
	short T;
};

struct SDStatus5
{
	short sDStatus[4];
};

struct SPress5
{
	long lPressure;
	long lAltitude;
};

struct SLonLat5
{
	long lLon;
	long lLat;
};

struct SGPSV5
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};

#endif