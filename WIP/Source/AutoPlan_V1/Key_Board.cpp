/**************************************************** Key_Board.c ***************************************************/
/* keyboard_000.c */
/******************************************************************************************************************/
/* 01-03-2013*/   /* @  */    /* DE1-0.2[001] */    /*  DaoHVN : Create new */
/******************************************************************************************************************/

#include "HEADER.h"
#include "RAM.h"
#include "FLAG.h"

#include "Key_Board.h"

#if (KEYBOARD_CONTROL == ENABLE)

pEventFunc EventFuncKey[iNUMKEY*3];

uint8_t vU08_ShiftKey[iNUMKEY];
uint8_t vU08_FlagKey[iNUMKEY];
uint8_t vU08_CounterKey[iNUMKEY];
uint8_t vU08_EventKey[iNUMKEY];
uint8_t vU08_RepeatKey[iNUMKEY];
uint8_t vU08_BufferInKey[iNUMKEY];


/* Key press function */
#if iNUMKEY > 0
void EVENT_KEY01_ON(void);    
void EVENT_KEY01_OFF(void);    
void EVENT_KEY01_PRESS(void);
#elif iNUMKEY > 1
void EVENT_KEY02_ON(void);    
void EVENT_KEY02_OFF(void);    
void EVENT_KEY02_PRESS(void);
#elif iNUMKEY > 2
void EVENT_KEY03_ON(void);    
void EVENT_KEY03_OFF(void);    
void EVENT_KEY03_PRESS(void);
#elif iNUMKEY > 3
void EVENT_KEY04_ON(void);    
void EVENT_KEY04_OFF(void);    
void EVENT_KEY04_PRESS(void);
#elif iNUMKEY > 4
void EVENT_KEY05_ON(void);    
void EVENT_KEY05_OFF(void);    
void EVENT_KEY05_PRESS(void);
#elif iNUMKEY > 5
void EVENT_KEY06_ON(void);    
void EVENT_KEY06_OFF(void);    
void EVENT_KEY06_PRESS(void);
#elif iNUMKEY > 6
void EVENT_KEY07_ON(void);    
void EVENT_KEY07_OFF(void);    
void EVENT_KEY07_PRESS(void);
#elif iNUMKEY > 7
void EVENT_KEY08_ON(void);    
void EVENT_KEY08_OFF(void);    
void EVENT_KEY08_PRESS(void);
#endif  /* iNUMKEY > 7 */

#if (KEYBOARD_MODE == i74LS165)
void ReadPinKeySerial(void)
{
  ;
}
#else
void ReadPinKeyParalel(void)
{
#if iNUMKEY > 0
  if(PINC0 == 0)
  {
    vU08_BufferInKey[0] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[0] = KEY_OFF;
  }
#elif iNUMKEY > 1
  if(PINC1 == 0)
  {
    vU08_BufferInKey[1] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[1] = KEY_OFF;
  }
#elif iNUMKEY > 2
  if(PINC2 == 0)
  {
    vU08_BufferInKey[2] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[2] = KEY_OFF;
  }
#elif iNUMKEY > 3
  if(PINC3 == 0)
  {
    vU08_BufferInKey[3] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[3] = KEY_OFF;
  }
#elif iNUMKEY > 4
  if(digitalRead() == 0)
  {
    vU08_BufferInKey[4] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[4] = KEY_OFF;
  }
#elif iNUMKEY > 5
  if(digitalRead() == 0)
  {
    vU08_BufferInKey[5] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[5] = KEY_OFF;
  }
#elif iNUMKEY > 6
  if(digitalRead() == 0)
  {
    vU08_BufferInKey[6] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[6] = KEY_OFF;
  }
#elif iNUMKEY > 7
  if(digitalRead() == 0)
  {
    vU08_BufferInKey[7] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[7] = KEY_OFF;
  }
#endif  /* iNUMKEY > 7 */
}
#endif  /* KEYBOARD_MODE */

void KeyBoard_Soft_Init(void)
{
  uint8_t i;
  
  for(i = 0;i < iNUMKEY;i ++)
  {
    vU08_ShiftKey[i]   = KEY_OFF_VALUE;
    vU08_FlagKey[i]    = KEY_OFF;
    vU08_CounterKey[i]   = 0x00;
    vU08_EventKey[i]   = EVT_KEY_NO;
    vU08_RepeatKey[i]  = FALSE;
    vU08_BufferInKey[i] = 0x00;
  }
#if iNUMKEY > 0
  EventFuncKey[0]  = EVENT_KEY01_ON;  
  EventFuncKey[1]  = EVENT_KEY01_OFF; 
  EventFuncKey[2]  = EVENT_KEY01_PRESS;
#elif iNUMKEY > 1
  EventFuncKey[3]  = EVENT_KEY02_ON;  
  EventFuncKey[4]  = EVENT_KEY02_OFF; 
  EventFuncKey[5]  = EVENT_KEY02_PRESS;
#elif iNUMKEY > 2
  EventFuncKey[6]  = EVENT_KEY03_ON;  
  EventFuncKey[7]  = EVENT_KEY03_OFF; 
  EventFuncKey[8]  = EVENT_KEY03_PRESS;
#elif iNUMKEY > 3
  EventFuncKey[9]  = EVENT_KEY04_ON;  
  EventFuncKey[10] = EVENT_KEY04_OFF; 
  EventFuncKey[11] = EVENT_KEY04_PRESS;
#elif iNUMKEY > 4
  EventFuncKey[12] = EVENT_KEY05_ON;  
  EventFuncKey[13] = EVENT_KEY05_OFF; 
  EventFuncKey[14] = EVENT_KEY05_PRESS;
#elif iNUMKEY > 5
  EventFuncKey[15] = EVENT_KEY06_ON;  
  EventFuncKey[16] = EVENT_KEY06_OFF; 
  EventFuncKey[17] = EVENT_KEY06_PRESS;
#elif iNUMKEY > 6
  EventFuncKey[18] = EVENT_KEY07_ON;  
  EventFuncKey[19] = EVENT_KEY07_OFF; 
  EventFuncKey[20] = EVENT_KEY07_PRESS;
#elif iNUMKEY > 7
  EventFuncKey[21] = EVENT_KEY08_ON;  
  EventFuncKey[22] = EVENT_KEY08_OFF; 
  EventFuncKey[23] = EVENT_KEY08_PRESS;
#endif
}
/************************** PINTC8~13 Interrupts ******************/
#if iNUMKEY > 0
ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{    
  if( (PINC & (1 << PINC0)) == 1 )
    {
        /* LOW to HIGH pin change */
    }
    else
    {
        /* HIGH to LOW pin change */
    }
    digitalWrite(11,(digitalRead(11)^1));
}
#elif iNUMKEY > 1
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
  digitalWrite(11,(digitalRead(11)^1));
}  
#elif iNUMKEY > 2
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
  digitalWrite(11,(digitalRead(11)^1));
}
#elif iNUMKEY > 3
ISR (PCINT3_vect) // handle pin change interrupt for D0 to D7 here
{
  digitalWrite(11,(digitalRead(11)^1));
}
#endif
void KeyBoard_Hard_Init(void)
{
  /* Port C is input */
  DDRC &= ~(iBIT0 | iBIT1 | iBIT2 | iBIT3);
  /* Pull Up register */
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  PCICR |= (1 << PCIE1);    /* set PCIE1 to enable PCMSK1 scan: Port C: PCINT8 ~ PCINT14 */
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10)| (1 << PCINT11);  /* set PCINT8~PCINT14 to trigger an interrupt on state change */
}

void UpdateKeyBoard(void)
{
  uint8_t i, utmp8;

  for(i = 0; i < iNUMKEY; i ++)
  {
    if(vU08_EventKey[i] < EVT_KEY_NO)
    {
      utmp8 = i*3 + vU08_EventKey[i];
      if(utmp8 < (iNUMKEY*3))
      {
        EventFuncKey[utmp8]();
      }
      vU08_EventKey[i] = EVT_KEY_NO;
    }
  }
}

/************************* KeyBoard_Cal ******************************/
/* Key Board Scan */
/* Call : 100ms */
/* Input: - */
/* Output: - */
/********************************************************************/
void KeyBoard_Cal(void)
{
  uint8_t i;
  
#if (KEYBOARD_MODE == i74LS165)          
  ReadPinKeySerial();
#else
  ReadPinKeyParalel(); 
#endif   
                     
  for(i = 0;i < iNUMKEY;i ++)      /* @  : For Check noise of keyboard */
  {      
                       
    if(vU08_BufferInKey[i] == KEY_ON)  
    {               
      vU08_ShiftKey[i] = KEY_ON_VALUE;
    }               
    else              
    {               
      vU08_ShiftKey[i] = KEY_OFF_VALUE;
    }               
#if 1
    if((vU08_ShiftKey[i] == KEY_ON_VALUE)&&(vU08_FlagKey[i] == KEY_OFF))  /*Key ON*/ 
    {
      vU08_EventKey[i] = EVT_KEY_ON;                        
      vU08_CounterKey[i] = TIME_KEY_REPEAT_FIRST;                       
      vU08_FlagKey[i] = KEY_ON;        
      digitalWrite(11,(digitalRead(11)^1));                   
    }
#endif    
    if((vU08_ShiftKey[i] != KEY_ON_VALUE)&&(vU08_FlagKey[i] == KEY_ON))   /*Key OFF */ 
    {
      vU08_EventKey[i] = EVT_KEY_OFF;                       
      vU08_ShiftKey[i] = KEY_OFF_VALUE;                       
      vU08_CounterKey[i] = 0x00;                      
      vU08_FlagKey[i] = KEY_OFF;      
      digitalWrite(11,(digitalRead(11)^1));                       
    }
    if((vU08_ShiftKey[i] == KEY_ON_VALUE)&&(vU08_CounterKey[i] > 0))    /*Key REPEAT*/ 
    {                                       
      vU08_CounterKey[i]--;                             
      if(vU08_CounterKey[i] == 0)                         
      {
        vU08_EventKey[i] = EVT_KEY_REPEAT;                    
        vU08_CounterKey[i] = TIME_KEY_REPEAT_SECOND;                    
        vU08_FlagKey[i] = KEY_ON;        
        digitalWrite(11,(digitalRead(11)^1));            
      }
    }
                                            
  }                              
}
#if iNUMKEY > 0
void EVENT_KEY01_ON(void)
{
  digitalWrite(11,(digitalRead(11)^1));
}

void EVENT_KEY01_OFF(void)
{

}

void EVENT_KEY01_PRESS(void)
{
  digitalWrite(8,(digitalRead(8)^1));
}
#elif iNUMKEY > 1
void EVENT_KEY02_ON(void)
{

}

void EVENT_KEY02_OFF(void)
{

}

void EVENT_KEY02_PRESS(void)
{

}
#elif iNUMKEY > 2
void EVENT_KEY03_ON(void)
{

}

void EVENT_KEY03_OFF(void)
{

}

void EVENT_KEY03_PRESS(void)
{
  
}
#elif iNUMKEY > 3
void EVENT_KEY04_ON(void)
{

}

void EVENT_KEY04_OFF(void)
{
  
}

void EVENT_KEY04_PRESS(void)
{

}
#elif iNUMKEY > 4
void EVENT_KEY05_ON(void)
{

}

void EVENT_KEY05_OFF(void)
{
  
}

void EVENT_KEY05_PRESS(void)
{
  
}
#elif iNUMKEY > 5
void EVENT_KEY06_ON(void)
{

}

void EVENT_KEY06_OFF(void)
{
  
}

void EVENT_KEY06_PRESS(void)
{

}
#elif iNUMKEY > 6
void EVENT_KEY07_ON(void)
{

}

void EVENT_KEY07_OFF(void)
{
  
}

void EVENT_KEY07_PRESS(void)
{
  
}
#elif iNUMKEY > 7
void EVENT_KEY08_ON(void)
{

}

void EVENT_KEY08_OFF(void)
{
  
}

void EVENT_KEY08_PRESS(void)
{
  
}
#endif  /* #elif iNUMKEY > 7 */


#endif  /* KEYBOARD_CONTROL == ENABLE */

/**********************end Key_Board.c ***********************/

