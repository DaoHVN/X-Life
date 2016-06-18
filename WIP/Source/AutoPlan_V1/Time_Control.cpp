#include "PREDEFINE.h"
#include "HEADER.h"
#include "RAM.h"
#include "FLAG.h"
#include "TIMER.h"

#if (TIME_CONTROL == ENABLE)

#include "Time_Control.h"

uint8_t vU08_TimerData[TIMER_CTRL_TBL_MAX][sizeof(timectrl)/sizeof(uint8_t)];

#if (EEPROM_CONTROL == ENABLE)
#include "EEPROM_Control.h"
#endif  /* (EEPROM_CONTROL == ENABLE) */

#if FAILSAFE_CONTROL == ENABLE
#include "FailSafe.h"
#endif

struct timectrl TIMER_TBL_DEFAULT[3] = 
{ /* Enable-Hour-Minute-Spend[3]-Spend[2]-Spend[1]-Spend[0] */
  {1,06,00,6,0},
  {1,11,00,11,0},
  {1,18,00,18,0}
};
struct timectrl TIMER_TBL_CTRL[TIMER_CTRL_TBL_MAX];

static void Timer_Check(void);
static void Timer_Read_EEPROM_FailSafe(void);

/*************** Timer_FailSafe ***************/
static void Timer_FailSafe(void)
{
  if(
    (vU08_Second <= 59) &&
    (vU08_Minutes <= 59) &&
    ((vU08_Hours <= 12) && (vU08_HoursMode == 12 )) &&
    ((vU08_Hours <= 24) && (vU08_HoursMode == 24 ))
    )
    {
      FailSafe_OK_judgement(FAILSAFE_REAL_TIME_READ);
    }
    else
    {
      FailSafe_NG_judgement(FAILSAFE_REAL_TIME_READ);
    }
}

static void Timer_Read_EEPROM_FailSafe(void)
{
  uint8_t i;
  uint32_t timespend;

  for (i = 0; i< TIMER_CTRL_TBL_MAX; i ++)
  {
    if (TIMER_CTRL_DATA[i].DATA.TIMER.Enable == 1)
    {
      timespend = (uint32_t)TIMER_CTRL_DATA[i].DATA.TIMER.Spend[3]<<24;
      timespend |= (uint32_t)TIMER_CTRL_DATA[i].DATA.TIMER.Spend[2]<<16;
      timespend |= (uint32_t)TIMER_CTRL_DATA[i].DATA.TIMER.Spend[1]<<8;
      timespend |= (uint32_t)TIMER_CTRL_DATA[i].DATA.TIMER.Spend[0];
      if (
          (((TIMER_CTRL_DATA[i].DATA.TIMER.Hour) > 12 && (vU08_HoursMode == 12)) ||
          ((TIMER_CTRL_DATA[i].DATA.TIMER.Hour > 24) && (vU08_HoursMode == 24))) ||
          (TIMER_CTRL_DATA[i].DATA.TIMER.Minute >= 60) ||
          (timespend > TIMER_CTRL_SPENDTIME_MAX)    
          )
      {
        FailSafe_NG_judgement(FAILSAFE_TIME_CTRL_READ_EEPROM);
      }
    }
  }
}

void Timer_Control(void)
{
  /* FailSafe Timer Read */
  Timer_FailSafe();

  /* Call Calcucate Time */
  Timer_Check(); 
}

static void Timer_Check(void)
{
  if (
    !TST_FAILSAFE(FAILSAFE_REAL_TIME_READ) && 
    !TST_FAILSAFE(FAILSAFE_TIME_CTRL_READ_EEPROM)
    )
  {
    
  }
}


static void Timer_Read_EEPROM_Data(void)
{
  uint8_t i,j;

  i = TIMER_EEPROM_START_ADD;
  for (j = 0; j < TIMER_CTRL_TBL_MAX; j ++)
  {
    EEPROM_Read_Page(i,&TIMER_CTRL_DATA[j].DATA.BYTE[0],7);
    i = i + 7;  /* start address eeprom */ 
  }
  /* FailSafe Timer EEPROM Read */
  Timer_Read_EEPROM_FailSafe();
}

void Timer_Control_Init(void)
{
  if (vU08_ErrorCode != 0x01)
  {
    Timer_Read_EEPROM_Data();
  }
}

#endif  /* TIME_CONTROL == ENABLE */


