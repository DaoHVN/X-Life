#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#if (TIME_CONTROL == ENABLE)
#include "PREDEFINE.h"

struct _timerflag
{
  uint8_t  dummy1           :1;   /* BIT7 */
  uint8_t  dummy2           :1;   /* BIT6 */
  uint8_t  dummy3           :1;   /* BIT5 */
  uint8_t  dummy4           :1;   /* BIT4 */
  uint8_t  dummy5           :1;   /* BIT3 */
  uint8_t  dummy6           :1;   /* BIT2 */
  uint8_t  dummy7           :1;   /* BIT1 */
  uint8_t  ExFlag           :1;   /* BIT0: Experience iflag */
};

struct timectrl
{
  struct _timerflag Control;
  union { 
    struct  {
      uint8_t Enable;
      uint8_t Hour;
      uint8_t Minute;
      uint8_t Spend[4];
    } TIMER;
    uint8_t BYTE[sizeof(TIMER)];
  } DATA;
};

/* Number of Save Time */
#define TIMER_CTRL_TBL_MAX          10
#define TIMER_EEPROM_START_ADD      0x0000
#define TIMER_EEPROM_END_ADD        (TIMER_EEPROM_START_ADD + (sizeof(timectrl)*TIMER_CTRL_TBL_MAX))
#define TIMER_CTRL_SPENDTIME_MAX    60000000 /* 0.1ms * 60.000.000 = 600.000 ms  = 10 min */

extern uint8_t vU08_TimerData[TIMER_CTRL_TBL_MAX][sizeof(timectrl)/sizeof(uint8_t)];

#define TIMER_CTRL_DATA   ((struct timectrl *)&vU08_TimerData)


extern void Timer_Control(void);
extern void Timer_Control_Init(void);
#endif  /* TIME_CONTROL == ENABLE */
#endif  /* TIME_CONTROL_H */

