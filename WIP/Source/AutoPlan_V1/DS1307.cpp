#include <Wire.h>
#include "RAM.h"
#include "FLAG.h"
#include "PREDEFINE.h"

#if ((TIME_CONTROL == ENABLE) && (TIME_MODE == iDS1307))

#include "DS1307.h"

static void DS1307_SaveTime(void);

/************************************* DS1307_Hard_Init *******************************************/
/* Hardware Initialize for RTC port */
/* Call : CPU_Init */
/**************************************************************************************************/
void DS1307_Hard_Init(void)
{
  DDRC |= (iBIT5);
	Wire.begin();
}
/************************************* DS1307_Soft_Init *******************************************/
/* Software Initialize for RTC module */
/* Call : CPU_Init */
/**************************************************************************************************/
void DS1307_Soft_Init(void)
{
	vU08_Second = 0;
	vU08_Minutes = 0;
	vU08_Hours = 0;
  vU08_HoursMode = 24;
  fU08_UpdateRealTime = 0;
}
/************************************* bcd_2_bin ***************************************************/
/* BCD  to decimal convert */
/* Call : --- */
/**************************************************************************************************/
static int bcd_2_bin(int temp)
{
	int a, b, c;
	a = temp;
	b = 0;
	if (a >= 16)
	{
		while (a >= 16)
		{
			a = a - 16;
			b = b + 10;
			c = a + b;
			temp = c;
		}
	}
	return temp;
}
/************************************* bin_to_bcd *************************************************/
/* decimal to BCD  convert */
/* Call : --- */
/**************************************************************************************************/
static int bin_2_bcd(int temp)
{
	int a, b, c;
	a = temp;
	b = 0;
	if (a >= 10)
	{
		while (a >= 10)
		{
			a = a - 10;
			b = b + 16;
			c = a + b;
			temp = c;
		}
	}
	return temp;
}
/************************************* DS1307_ReadTime *******************************************/
/* Read Real Time from DS1307 in I2C interface */
/* Call : 100 ms */
/**************************************************************************************************/
void DS1307_ReadTime(void)
{
  uint16_t utmp16;

#if (SIM_DEBUG == ENABLE)
    //Serial.println(" Read Time \n");
#endif
  if( !TSTBIT(fU08_UpdateRealTime) )
  {
    /* Send the address 0x68 to connect DS1307 */
    Wire.beginTransmission(DS1307_ADD);
    /* Sending address */
    Wire.write(DS1307_START_ADD);
    /* The end of the IIC communication */
    Wire.endTransmission();
    /* IIC communication is started, you can continue to access another address (address auto increase) and the number of visits */
    Wire.requestFrom(DS1307_ADD, DS1307_TIME_ADD);
    /* read time */
    vU08_Second = (uint8_t)bcd_2_bin(Wire.read());
    vU08_Minutes = (uint8_t)bcd_2_bin(Wire.read());
    utmp16 = Wire.read();
    vU08_Hours = (uint8_t)bcd_2_bin(utmp16);
    if (utmp16 & 0x80)
    {
      vU08_HoursMode = 24;
    }
    else
    {
      vU08_HoursMode = 12;
    }
    vU08_DayOfWeek = (uint8_t)Wire.read();
    utmp16 = Wire.read();
    utmp16 = Wire.read();
    utmp16 = Wire.read();
#if (SIM_DEBUG == ENABLE)
    //Serial.print(vU08_Hours);
    //Serial.print(" Gio ");
    //Serial.println(vU08_Minutes);
#endif
  }
  else  /* Save new Real Time */
  {    
    DS1307_SaveTime();
    CLRBIT(fU08_UpdateRealTime);
  }      
}

static void DS1307_SaveTime(void)
{
  /* Send the address 0x68 to connect DS1307 */
  Wire.beginTransmission(DS1307_ADD);
  Wire.write((byte) 0);
  Wire.write(bin_2_bcd(23));  /* Sec */
  Wire.write(bin_2_bcd(25));  /* Min */
  Wire.write(bin_2_bcd(13));  /* Hour */
  Wire.write(5);
  Wire.write((byte) 0);
  Wire.endTransmission();
}

#endif  /* ( (TIME_CONTROL == ENABLE) &&  (TIME_MODE == iDS1307) ) */

