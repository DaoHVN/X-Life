#ifndef JOB_H
#define JOB_H

#include "PREDEFINE.h"

#define NUMBER_JOB_100MS        3
#define NUMBER_JOB_1SEC         0

#if (TIME_CONTROL == ENABLE)
#if (TIME_MODE == iDS1307)
#include "Time_Control.h"
#endif
#endif

#if (WIFI_CONTROL == ENABLE)
#if (WIFI_MODE == iESP8266)
#include "ESP8266.h"
#endif
#endif

#if (KEYBOARD_CONTROL == ENABLE)
#include "Key_Board.h"
#endif

#if (ADC_CONTROL == ENABLE)
#include "ADC.h"
#endif

/********************* 100 mili second Job table *****************************/
#if NUMBER_JOB_100MS != 0
void (*const JOB_100ms[])() =
{
  KeyBoard_Cal,     /* 1 */
  ADC_Control,      /* 2 */
  Timer_Control     /* 3 */
};
#endif

/********************* 1 second Job table *****************************/
#if NUMBER_JOB_1SEC != 0
void ( *const JOB_1sec[])()
{
  
};
#endif

#endif /* JOB_H */

