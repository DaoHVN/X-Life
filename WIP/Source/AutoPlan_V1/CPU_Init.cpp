#include "PREDEFINE.h"
#include "TimerOne.h"
#include "OS.h"

#include "CPU_Init.h"

#if (TIME_CONTROL == ENABLE)
#if (TIME_MODE == iDS1307)
#include "DS1307.h"
#endif
#endif

#if (WIFI_CONTROL == ENABLE)
#if (WIFI_MODE == iESP8266)
#include "ESP8266.h"
#endif
#endif

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

#if (EEPROM_CONTROL == ENABLE)
#include "EEPROM_Control.h"
#endif

void Timer_Init(void);

void IO_init(void);

/************************************* Hardware_init **********************************************/
/* Hardware, IO, Timer Init */
/* Call : Setup ( Power ON ) */
/**************************************************************************************************/
void Hardware_init(void)
{
  /* Input/ Output PORT init */
  IO_init();
  
  /* Timer Init */
  Timer_Init();

  /* Serial trace init */
#if (SIM_DEBUG == ENABLE)
    Serial.begin(SIM_DEBUG_BAUDRATE);
#endif
  /* Wifi control init */
#if (WIFI_CONTROL == ENABLE)
#if (WIFI_MODE == iESP8266)
  ESP8266_Hard_Init();
#endif
#endif
  
  /* Real Time control init */
#if (TIME_CONTROL == ENABLE)
#if (TIME_MODE == iDS1307)
  DS1307_Hard_Init();
#endif
#endif
  
  /* Display init */
#if (DISPLAY_CONTROL == ENABLE)
#if (DISPLAY_MODE == iNOKIA5110)  
  LCD5110_Hard_Init();
#elif (DISPLAY_MODE == iLCD16X02)
  LCD1602_Hard_Init();
#endif
#endif
  
  /* KeyBoard Init */
#if (KEYBOARD_CONTROL == ENABLE)
  KeyBoard_Hard_Init();
#endif

#if (SIM_DEBUG == ENABLE)
  Serial.println("HardWare Init Finish\n");
#endif
  return;
}
/************************************* Software_init **********************************************/
/* Global Variant Init */
/* Call : Setup ( Power ON ) */
/**************************************************************************************************/
void Software_init(void)
{
  /* Real Time Init */
#if (TIME_CONTROL == ENABLE)
#if (TIME_MODE == iDS1307)
  DS1307_Soft_Init();
#endif
#endif
  
  /* Wifi Init */
#if (WIFI_CONTROL == ENABLE)
#if (WIFI_MODE == iESP8266)  
  ESP8266_Soft_Init();
#endif
#endif

  /* KeyBoard Init */
#if (KEYBOARD_CONTROL == ENABLE)
  KeyBoard_Soft_Init();
#endif

#if (EEPROM_CONTROL == ENABLE)
  EEPROM_Read_Init();
#endif

#if (SIM_DEBUG == ENABLE)
  Serial.println("Software Init Finish\n");
#endif
  return;
}
/************************************* Timer_Init *************************************************/
/* Timer 1 interrupts init */
/* Call : Hardware_init */
/**************************************************************************************************/
void Timer_Init(void)
{
  /* Init Timer 1 */
  /* 100000 us = 100 ms = 0.1 sec */
  Timer1.initialize(100000);
  /* Interrupt OS call 100 ms */
  Timer1.attachInterrupt(OS_Control);
}
/************************************* IO_init ****************************************************/
/* Input/Output init */
/* Call : Hardware_init */
/**************************************************************************************************/
void IO_init(void)
{
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
}
