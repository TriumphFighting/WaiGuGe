#ifndef _USART4_
#define _USART4_
#include"sys.h"

void USART4_InterRupt_Init(void);

int GetPresentAngle4(void);

struct STime4
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc4
{
	short a[3];
	short T;
};
struct SGyro4
{
	short w[3];
	short T;
};
struct SAngle4
{
	short Angle[3];
	short T;
};
struct SMag4
{
	short h[3];
	short T;
};

struct SDStatus4
{
	short sDStatus[4];
};

struct SPress4
{
	long lPressure;
	long lAltitude;
};

struct SLonLat4
{
	long lLon;
	long lLat;
};

struct SGPSV4
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};

#endif
