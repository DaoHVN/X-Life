#ifndef ADC_H
#define ADC_H

#include "PREDEFINE.h"

#if (ADC_CONTROL == ENABLE)

#define ANALOG_NUM_CHANNEL      1
#define ANALOG_PIN_1            0

extern void ADC_Hard_Init(void);
extern void ADC_Control(void);
#endif  /* (ADC_CONTROL == ENABLE) */

#endif
