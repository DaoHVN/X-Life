#ifndef DS1307_H
#define DS1307_H

#include "PREDEFINE.h"

#if ((TIME_CONTROL == ENABLE) && (TIME_MODE == iDS1307))

#define DS1307_ADD            0x68
#define DS1307_START_ADD      0x00
#define DS1307_TIME_ADD       0x07

#define DS1307_CONTROL_REGISTER 0x07
#define DS1307_RAM_REGISTER     0x08

// DS1307 Control register bits.
#define RTC_DS1307__RS0         0x00
#define RTC_DS1307__RS1         0x01
#define RTC_DS1307__SQWE        0x04
#define RTC_DS1307__OUT         0x07

extern void DS1307_Hard_Init(void);
extern void DS1307_Soft_Init(void);
extern void DS1307_ReadTime(void);

#endif  /* ( (TIME_CONTROL == ENABLE) &&  (TIME_MODE == iDS1307) ) */

#endif /* DS1307_H */



