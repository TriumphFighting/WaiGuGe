#ifndef _BEEP_H
#define _BEEP_H

#include"sys.h"

#define BEEP PBout(8)

void Beep_Init(void);

void Beep_AllInitFinish(void);
void Beep_StandUp(void);
void Beep_Walk(void);
void Beep_SitDown(void);
void Beep_Stop(void);

#endif








