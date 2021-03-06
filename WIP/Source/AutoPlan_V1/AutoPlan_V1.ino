#include "HEADER.h"
#include "PREDEFINE.h"
#include "CPU_Init.h"
#include "OS.h"
#include "RAM.h"
#include "FLAG.h"

#if (DISPLAY_CONTROL == ENABLE)
#if (DISPLAY_MODE == iNOKIA5110)
#include "LCD_5110.h"
#elif (DISPLAY_MODE == iLCD16X02)
#include "LCD_1602.h"
#endif
#endif

#if (KEYBOARD_CONTROL == ENABLE)
#include "Key_Board.h"
#endif

#if ((TIME_CONTROL == ENABLE) && (TIME_MODE == iDS1307))
#include "DS1307.h"
#endif

#if (FAILSAFE_CONTROL == ENABLE)
#include "FailSafe.h"
#endif
/*****************************************************************/
/* Power On Initialize */
/*****************************************************************/
void setup() 
{
  /* Disable interrupts */
  Disable_Int();
  /* Register Init */
  Hardware_init();
  /* Global Variant initialize */
  Software_init();
  /* Enable all interrupts */
#if (SIM_DEBUG == ENABLE)
  Serial.println(vU08_ErrorCode);
#endif
  Enable_Int();
}
/*****************************************************************/
/* Main function */
/*****************************************************************/
void loop() 
{
  while(1)
  {
    /* Keyboard Scan */
#if (KEYBOARD_CONTROL == ENABLE)
    UpdateKeyBoard();
#endif
    /* Real Time Read */
#if ((TIME_CONTROL == ENABLE) && (TIME_MODE == iDS1307))
    DS1307_ReadTime();
#endif
    /* Error  Report */
#if (FAILSAFE_CONTROL == ENABLE)
    FailSafe_judgement();
#endif
    /* Display to screen */
#if (DISPLAY_CONTROL == ENABLE)
    Update_Display();
#endif
  }
} 

