#ifndef RAM_H
#define RAM_H

#include "HEADER.h"
#include "PREDEFINE.h"

typedef void (*pEventFunc)(void);
typedef void (*pEventFuncInput)(unsigned char *p);

/*** struct variable - need be back up ***/
struct  lst_glb_bk
{
  uint8_t dummy;
};

extern  struct lst_glb_bk vListBk, vListBk_z;
/**************************************************************************/


/*** struct variable - do not need be back up ***/
struct lst_glb
{
#if (TIME_CONTROL == ENABLE)
  uint8_t Second;
  uint8_t Minutes;
  uint8_t Hours;
  uint8_t HoursMode;
  uint8_t DayOfWeek;
#endif
  uint8_t ErrorCode;
};
extern struct lst_glb vList;
/**************************************************************************/
#if (TIME_CONTROL == ENABLE)
#define vU08_Second               vList.Second
#define vU08_Minutes              vList.Minutes
#define vU08_Hours                vList.Hours
#define vU08_HoursMode            vList.HoursMode
#define vU08_DayOfWeek            vList.DayOfWeek
#endif  /* (TIME_CONTROL == ENABLE) */

#define vU08_ErrorCode            vList.ErrorCode

#endif  /* RAM_H */

