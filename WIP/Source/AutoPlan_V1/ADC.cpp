#include "HEADER.h"
#include "ADC.h"
#include "RAM.h"

#if (ADC_CONTROL == ENABLE)
void ADC_Hard_Init(void)
{
  
}

static uint16_t ADC_Read_Channel(uint8_t channel)
{
  uint16_t adc;

  adc = analogRead(channel);

  return (adc);
}

void ADC_Control(void)
{
  uint32_t utmp32;
  uint8_t ho,mi;
  
  vU16_ADCValue = ADC_Read_Channel(ANALOG_PIN_1);
  utmp32 = (uint32_t)(vU16_ADCValue * 1440);
  utmp32 = utmp32 / 1023;
  ho = (uint8_t)(utmp32 / 60);
  mi = (uint8_t)(utmp32 - (ho * 60));
#if SIM_DEBUG == ENABLE
  Serial.print("ADC value: ");
  Serial.println(vU16_ADCValue);
  Serial.print("Time: ");
  Serial.print(ho);
  Serial.print(" : ");
  Serial.println(mi);
#endif
  
}
#endif  /* (ADC_CONTROL == ENABLE) */

