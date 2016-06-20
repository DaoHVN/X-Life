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

#define P_EVENT     0

#if P_EVENT != 0
pEventFunc EventFuncKey[iNUMKEY*3];
#endif

static uint8_t vU08_ShiftKey[iNUMKEY];
static uint8_t vU08_FlagKey[iNUMKEY];
static uint8_t vU08_CounterKey[iNUMKEY];
static uint8_t vU08_EventKey[iNUMKEY];
static uint8_t vU08_BufferInKey[iNUMKEY];


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
  if(digitalRead(4) == 0)
  {
    vU08_BufferInKey[0] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[0] = KEY_OFF;
  }
#elif iNUMKEY > 1
  if(digitalRead(5) == 0)
  {
    vU08_BufferInKey[1] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[1] = KEY_OFF;
  }
#elif iNUMKEY > 2
  if(digitalRead(6) == 0)
  {
    vU08_BufferInKey[2] = KEY_ON;
  }
  else
  {
    vU08_BufferInKey[2] = KEY_OFF;
  }
#elif iNUMKEY > 3
  if(digitalRead(7) == 0)
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
    vU08_CounterKey[i]   = TIME_KEY_REPEAT_FIRST;
    vU08_EventKey[i]   = EVT_KEY_NO;
    vU08_BufferInKey[i] = 0x00;
  }
#if P_EVENT != 0
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
#endif  /* #if P_EVENT != 0 */
}

void KeyBoard_Hard_Init(void)
{
  /* Port D is input */
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
}

void UpdateKeyBoard(void)
{
  uint8_t i, utmp8;

  for(i = 0; i < iNUMKEY; i ++)
  {
    if(vU08_EventKey[i] < EVT_KEY_NO)
    {
#if iNUMKEY > 0
      if (i == 0)
      {
        if (vU08_EventKey[i] == EVT_KEY_ON)
        {
          EVENT_KEY01_ON();
        }
        else if (vU08_EventKey[i] == EVT_KEY_OFF)
        {
          EVENT_KEY01_OFF();
        }
        else  /* key press */
        {
          EVENT_KEY01_PRESS();
        }
      }
#elif iNUMKEY > 1      
      else if (i == 1)
      {
        if (vU08_EventKey[i] == EVT_KEY_ON)
        {
          EVENT_KEY02_ON();
        }
        else if (vU08_EventKey[i] == EVT_KEY_OFF)
        {
          EVENT_KEY02_OFF();
        }
        else  /* key press */
        {
          EVENT_KEY02_PRESS();
        }               
      }
#elif iNUMKEY > 2       
      else if (i == 2)
      {
        if (vU08_EventKey[i] == EVT_KEY_ON)
        {
          EVENT_KEY03_ON();
        }
        else if (vU08_EventKey[i] == EVT_KEY_OFF)
        {
          EVENT_KEY03_OFF();
        }
        else  /* key press */
        {
          EVENT_KEY03_PRESS();
        }               
      }
#elif iNUMKEY > 3       
      else
      {
        if (vU08_EventKey[i] == EVT_KEY_ON)
        {
          EVENT_KEY04_ON();
        }
        else if (vU08_EventKey[i] == EVT_KEY_OFF)
        {
          EVENT_KEY04_OFF();
        }
        else  /* key press */
        {
          EVENT_KEY04_PRESS();
        }         
      }
#endif      
#if P_EVENT != 0
      utmp8 = (uint8_t)(i*3 + vU08_EventKey[i]);
      if(utmp8 < (iNUMKEY*3))
      {
        //EventFuncKey[utmp8]();
      }
      vU08_EventKey[i] = EVT_KEY_NO;
#endif
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
    vU08_ShiftKey[i] = vU08_ShiftKey[i] << 1;                   
    if(vU08_BufferInKey[i] == KEY_ON)  
    {               
      vU08_ShiftKey[i] |= 0x01;
    }               
    else              
    {               
      vU08_ShiftKey[i] |= 0x00;
    }               
    /* Key OFF -> ON */
    if(((vU08_ShiftKey[i]&KEY_ON_VALUE) == KEY_ON_VALUE) && (vU08_FlagKey[i] == KEY_OFF))   
    {
      vU08_EventKey[i] = EVT_KEY_ON;                        
      vU08_CounterKey[i] = TIME_KEY_REPEAT_FIRST;                       
      vU08_FlagKey[i] = KEY_ON;              
    }
    /* Key ON -> OFF */
    if(((vU08_ShiftKey[i]&KEY_ON_VALUE) != KEY_ON_VALUE) && (vU08_FlagKey[i] == KEY_ON))    
    {
      vU08_EventKey[i] = EVT_KEY_OFF;                       
      vU08_ShiftKey[i] = KEY_OFF_VALUE;                       
      vU08_FlagKey[i] = KEY_OFF;                          
    }
    /* Key PRESS */ 
    if(((vU08_ShiftKey[i]&KEY_ON_VALUE) == KEY_ON_VALUE) && (vU08_CounterKey[i] > 0))    
    {                  
      if (vU08_CounterKey[i] > 0)
      {
        vU08_CounterKey[i]--;                       
      }
      if(vU08_CounterKey[i] == 0)                         
      {
        vU08_EventKey[i] = EVT_KEY_REPEAT;                    
        vU08_CounterKey[i] = TIME_KEY_REPEAT_SECOND;                    
        vU08_FlagKey[i] = KEY_ON;             
      }
    }                               
  }                             
}
#if iNUMKEY > 0
void EVENT_KEY01_ON(void)
{
  
}

void EVENT_KEY01_OFF(void)
{

}

void EVENT_KEY01_PRESS(void)
{
  
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

