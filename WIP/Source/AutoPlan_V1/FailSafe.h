/*************************************************************************************************/
/*  [@] 20151228  DaoHVN  SPEC: Diagnosis base: Create new Module Diagnosis */
/*************************************************************************************************/
#ifndef FAILSAFE_H
#define FAILSAFE_H

#include "HEADER.h"
#include "PREDEFINE.h"
#include "RAM.h"
#include "FLAG.h"

#if (FAILSAFE_CONTROL == ENABLE)

struct failsafe_tbl
{
  uint8_t  FailCode;            /* Fail Code */
  uint8_t  TimeSpend;           /* Timer Check Error: x 1sec */
};
struct  failsafe_data
{
  uint8_t Running;             /* Diagnosis is inprogress */
  uint8_t Abnormal;            /* Diagnosis is Abnormal */
  uint8_t NGCounter;           /* Timer count when NG judgement */
  uint8_t OKCounter;           /* Timer count when OK judgement */
} ;
#define NUMBER_FAILSAFE          3
extern struct failsafe_data FAILSAFE_DATA[NUMBER_FAILSAFE];

#define TST_FAILSAFE(dgn) ((FAILSAFE_DATA[dgn].Abnormal)==(1))

/*** MACRO Diagnosis Define here ***/
#define FAILSAFE_EEPROM_INIT_READ         0x00
#define FAILSAFE_REAL_TIME_READ           0x01
#define FAILSAFE_REAL_SAVETIME_READ       0x02

extern void FailSafe_NG_judgement(uint8_t dgn);
extern void FailSafe_OK_judgement(uint8_t dgn);
extern void FailSafe_judgement(void);
extern void FailSafe_timer_counter(void);

#endif  /* (FAILSAFE_CONTROL == ENABLE) */

#endif /* FAILSAFE_HEADER_H */

