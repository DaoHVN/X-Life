#ifndef FLAG_H
#define FLAG_H

#include "HEADER.h"
#include "PREDEFINE.h"

struct _flag_list{
#if (DISPLAY_CONTROL == ENABLE)
  uint8_t UpdateDisplay           :1;
#endif
#if ((TIME_CONTROL == ENABLE) && (TIME_MODE == iDS1307))
  uint8_t UpdateRealTime           :1;
#endif
#if (EEPROM_CONTROL == ENABLE)
  uint8_t EEPROMInitNG              :1;
#endif
#if (ADC_CONTROL == ENABLE)
  uint8_t ADCStartConvert           :1;
#endif
};
extern struct _flag_list flag_list;
/****************** define global flag dont need backup here ***********************************************/
#define fU08_UpdateDisplay        flag_list.UpdateDisplay
#define fU08_UpdateRealTime       flag_list.UpdateRealTime
#define fU08_EEPROMInitNG         flag_list.EEPROMInitNG
#define fU08_ADCStartConvert      flag_list.ADCStartConvert
/***********************************************************************************************************/

struct _flag_list_z{
#if (TEMP_CONTROL == ENABLE)
  uint8_t Temp           :1;
#endif  
};

extern struct _flag_list_z flag_list_z,flag_list_z_bk;


/************************************* define flag z here **************************************************/
#if (TEMP_CONTROL == ENABLE)
#define fU08_Temp          flag_list_z.Temp;
#define fU08_Temp_z        flag_list_z_bk.Temp;
#endif


/***********************************************************************************************************/
/* define flag here*/
#endif  /* FLAG_H */

