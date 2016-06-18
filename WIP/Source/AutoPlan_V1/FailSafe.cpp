/*************************************************************************************************/
/*  [@] 20151228  DaoHVN  SPEC: Diagnosis base: Create new Module Diagnosis */
/*************************************************************************************************/
#include "FailSafe.h"

#if (FAILSAFE_CONTROL == ENABLE)

#define FAILSAFE_OK_COUNTER        3

static const  struct  failsafe_tbl FAILSAFE_TBL[NUMBER_FAILSAFE] =
{
      /*Code*/ /*Count*/
/*0*/ {0x00,0x00},  /* FAILSAFE_EEPROM_INIT_READ */
/*1*/ {0x01,0x0A},  /* FAILSAFE_REAL_TIME_READ */
/*1*/ {0x02,0x00}   /* FAILSAFE_TIME_CTRL_READ_EEPROM */
};

struct failsafe_data FAILSAFE_DATA[NUMBER_FAILSAFE];

/************************************************************/
/* Function    : FAILSAFE_NG_judgement             */
/* Description : Diagnosis NG judgement           */
/* Argument    : Diagnosis number channel         */
/* Return      : None                   */
/************************************************************/
void FailSafe_NG_judgement(uint8_t dgn)
{
  if (dgn < NUMBER_FAILSAFE)
  {
    if(FAILSAFE_DATA[dgn].Running == DISABLE)
    {
      FAILSAFE_DATA[dgn].Running = ENABLE;
      StartTimer(FAILSAFE_DATA[dgn].NGCounter,FAILSAFE_TBL[dgn].TimeSpend);
    }
  }
}
/************************************************************/
/* Function    : FAILSAFE_OK_judgement             */
/* Description : Diagnosis OK judgement           */
/* Argument    : Diagnosis number channel         */
/* Return      : None                   */
/************************************************************/
void FailSafe_OK_judgement(uint8_t dgn)
{
  if (dgn < NUMBER_FAILSAFE)
  {
    if (FAILSAFE_DATA[dgn].Running == ENABLE)
    {
      if (FAILSAFE_DATA[dgn].OKCounter >= FAILSAFE_OK_COUNTER)
      {
        FAILSAFE_DATA[dgn].Running = DISABLE;
        FAILSAFE_DATA[dgn].Abnormal = 0;
        FAILSAFE_DATA[dgn].OKCounter = 0;
      }
      else
      {
        FAILSAFE_DATA[dgn].OKCounter ++;
      }
    }
    else  /* not running */
    {
      FAILSAFE_DATA[dgn].Abnormal = 0;
      FAILSAFE_DATA[dgn].OKCounter = 0;
    }
  }
}
/************************************************************/
/* Function    : FailSafe_judgement                */
/* Description : Diagnosis judgement            */
/* Argument    : None                   */
/* Return      : None                   */
/************************************************************/
void FailSafe_judgement(void)
{
  uint8_t i;
  uint8_t uc8_fail_tmp;

  for (i = 0;((i < NUMBER_FAILSAFE)&&(vU08_ErrorCode != 0)); i++)
  {
    if (CheckTimer(FAILSAFE_DATA[i].NGCounter) &&
       (FAILSAFE_DATA[i].Running == ENABLE))
    {
      FAILSAFE_DATA[i].Abnormal = 1;
      FAILSAFE_DATA[i].OKCounter = 0;
      FAILSAFE_DATA[i].Running = DISABLE;
    }
    if (FAILSAFE_DATA[i].Abnormal == 1)
    {
      vU08_ErrorCode = FAILSAFE_TBL[i].FailCode;
    }
  }
}

/************************************************************/
/* Function    : FAILSAFE_timer_counter              */
/* Description : Diagnosis counter timer          */
/* Argument    : None                   */
/* Return      : None                   */
/************************************************************/
void FailSafe_timer_counter(void)
{
  uint8_t i;
  
  for (i = 0; i < NUMBER_FAILSAFE; i++)
  {
    if(FAILSAFE_DATA[i].NGCounter != 0)
    {
      FAILSAFE_DATA[i].NGCounter --;  
    }
  }
}
#endif  /* FAILSAFE_CONTROL */

