#ifndef _USART1_
#define _USART1_
#include"sys.h"

void USART1_InterRupt_Init(void);
void UART1_Put_Char(unsigned char DataToSend);
void UART1_Put_String(unsigned char *Str);
int GetPresentAngle1(void);

struct STime1
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc1
{
	short a[3];
	short T;
};
struct SGyro1
{
	short w[3];
	short T;
};
struct SAngle1
{
	short Angle[3];
	short T;
};
struct SMag1
{
	short h[3];
	short T;
};

struct SDStatus1
{
	short sDStatus[4];
};

struct SPress1
{
	long lPressure;
	long lAltitude;
};

struct SLonLat1
{
	long lLon;
	long lLat;
};

struct SGPSV1
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};


#endif

