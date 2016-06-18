#include <EEPROM.h>
#include "PREDEFINE.h"
#include "HEADER.h"
#include "FLAG.h"

#if (EEPROM_CONTROL == ENABLE)
#include "EEPROM_Control.h"

#if (FAILSAFE_CONTROL == ENABLE)
#include "FailSafe.h"
#endif

void EEPROM_Write_Page(uint16_t address, uint8_t *data, uint16_t len)
{
  uint16_t i;

  if (data != NULL)
  {
    for (i = 0; i< len; i ++)
    {
      EEPROM.write(address, data[i]);
    }
  }
}

void EEPROM_Read_Page(uint16_t address, uint8_t *data, uint16_t len)
{
  uint16_t i;

  if (data != NULL)
  {
    for (i = 0; i< len; i ++)
    {
      data[i] = EEPROM.read(address);
    }
  }
}

void EEPROM_Read_Init(void)
{
  uint8_t eep_data;
  uint16_t i;

  SETBIT(fU08_EEPROMInitNG);
  for (i = EEPROM_START_ADDRESS;i < EEPROM_END_ADDRESS; i++)
  {
    eep_data = EEPROM.read(i);
    if (eep_data != 0xFF)
    {
      CLRBIT(fU08_EEPROMInitNG);
    }
  }
  if (TSTBIT(fU08_EEPROMInitNG))
  {
#if (FAILSAFE_CONTROL == ENABLE)
    FailSafe_NG_judgement(FAILSAFE_EEPROM_INIT_READ);  
#endif
  }
}

#endif  /* (EEPROM_CONTROL == ENABLE) */

