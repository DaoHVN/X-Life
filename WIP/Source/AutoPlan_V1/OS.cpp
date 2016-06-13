#include "HEADER.h"
#include "OS.h"
#include "TIMER.h"
#include "JOB.h"

#if (FAILSAFE_CONTROL == ENABLE)
#include "FailSafe.h"
#endif

static uint8_t vU08_TimerCounter = 0;   /* Unit:[ms] - Resolution:[100] */
static uint8_t vU08_TimerJob = 0;       /* Unit:[ms] - Resolution:[100] */
static uint8_t fU08_Job100ms = 0;       /* Unit:[-] - Resolution:[-] */
static uint8_t fU08_Job1sec = 0;        /* Unit:[-] - Resolution:[-] */
static uint8_t fUC8_JobRunning = 0;     /* Unit:[-] - Resolution:[-] */
/************************************* Enable_Int *************************************************/
/* Enabel all interrupts */
/**************************************************************************************************/
void Enable_Int(void)
{
  interrupts();
}
/************************************* Disable_Int *************************************************/
/* Disable all interrupt */
/**************************************************************************************************/
void Disable_Int(void)
{
  noInterrupts();
}
/************************************* TimerCount *************************************************/
/* Count down Global Timer Variant was defined in TIMER.h */
/* Call each 100ms */
/**************************************************************************************************/
static void TimerCount(void)
{
  vU08_TimerCounter ++;
#if (FAILSAFE_CONTROL == ENABLE)
  FailSafe_timer_counter();
#endif
  /* decrement 1Byte(uint8_t) 1SKC Timer Variable */
#if timer100ms_8bit_on != 0
  uint8_t *p8;
  for( p8 = ( uint8_t* ) &timer100ms_8bit ;
     p8 < ( uint8_t* )&timer100ms_8bit + sizeof( timer100ms_8bit ) / sizeof( uint8_t ) ;
     p8++ )
  {
    if( *p8 > 0 )
    {
      (*p8)-- ;
    }
  }
#endif  /* timer100ms_8bit_on != 0 */

  if( vU08_TimerCounter >= 10 ) /* 100ms * 10 = 1sec */
  {
#if timer1s_8bit_on != 0
    uint8_t *p8;
    for( p8 = ( uint8_t* ) &timer1s_8bit ;
       p8 < ( uint8_t* )&timer1s_8bit + sizeof( timer1s_8bit ) / sizeof( uint8_t ) ;
       p8++ )
    {
      if( *p8 > 0 )
      {
        (*p8)-- ;
      }
    }
#endif /* timer1s_8bit_on != 0 */
    vU08_TimerCounter = 0;
  }
}
/************************************* OS_Control *************************************************/
/* Call All function process Data */
/* Call each 100ms */
/**************************************************************************************************/
void OS_Control(void)
{
  uint8_t i;

  /* Timer Count Down each 100ms */
  TimerCount();
  
  /* 100ms Job running flag */
  SETBIT(fU08_Job100ms);

  /* 1s Job running flag */
  if(vU08_TimerJob < 10)
  {
    vU08_TimerJob ++;
  }
  else
  {
    SETBIT(fU08_Job1sec);
    vU08_TimerJob = 0;
  }
  digitalWrite(13,(digitalRead(13)^1));
#if 1
  if (TSTBIT(fUC8_JobRunning)) /* IO JOB is running now! */
  {
    /* nothing if have JOB running */
  }
  else
  {
    SETBIT(fUC8_JobRunning);
    do
    {
      if( TSTBIT(fU08_Job100ms) )
      {
        /* JOB 100ms call */
#if NUMBER_JOB_100MS != 0
        for(i = 0; i < NUMBER_JOB_100MS; i++)
        {
          JOB_100ms[i]();  /* Call JOB function 100ms */
        }
#endif
        CLRBIT(fU08_Job100ms);
      }
      else if( TSTBIT(fU08_Job1sec) )
      {
        /* JOB 1 sec call */
#if NUMBER_JOB_1SEC != 0
        for(i = 0; i < NUMBER_JOB_1SEC; i++)
        {
          (*JOB_1sec[i]());  /* Call JOB function 1s */
        }
#endif        
        CLRBIT(fU08_Job1sec);
      }
      else  /* no JOB Run */
      {
        CLRBIT(fUC8_JobRunning);
      }
    } while(TSTBIT(fUC8_JobRunning));
  }
#endif  /* #if 0 */
}


