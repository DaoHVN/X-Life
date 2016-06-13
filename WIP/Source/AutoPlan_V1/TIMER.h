#ifndef TIMER_H
#define TIMER_H

#include "HEADER.h"

#define timer100ms_8bit_on      1
#define timer1s_8bit_on         1

#if timer100ms_8bit_on != 0

struct _timer100ms_8bit{
#if WIFI_CONTROL == ENABLE
  uint8_t WifiWaitTime;
#endif
};

extern struct _timer100ms_8bit timer100ms_8bit;

/******************************************************************************/
/* define Global Timer Here */
#define tU08_WifiWaitTime                         timer100ms_8bit.WifiWaitTime
/******************************************************************************/
#endif  /* timer100ms_8bit_on != 0 */

/******************************************************************************/

#if timer1s_8bit_on != 0
struct _timer1s_8bit {
  uint8_t TimerFailSafe;
};

extern struct _timer1s_8bit timer1s_8bit;


/******************************************************************************/
/* define Global Timer Here */
#define tU08_TimerFailSafe                         timer1s_8bit.TimerFailSafe
/******************************************************************************/

#endif  /* timer100ms_16bit_on != 0 */

#endif  /* TIMER_H */


