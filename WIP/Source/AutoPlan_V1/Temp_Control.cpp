#include "PREDEFINE.h"
#include "HEADER.h"
#include "RAM.h"
#include "FLAG.h"

#include "Temp_Control.h"

#if ( (TEMP_MODE == iDHT11) || (TEMP_MODE == iDHT22) )
#include "dht.h"
#endif

#if TEMP_CONTROL == ENABLE
void Temp_Calculate(void)
{
  
}
void Temp_Control(void);

#endif  /* TEMP_CONTROL == ENABLE */

