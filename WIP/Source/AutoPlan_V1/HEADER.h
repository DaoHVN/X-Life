#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <wiring.h>
#endif

/***************** data length define ***************/
#define SINT8MIN    -128
#define SINT8MAX    127
#define UINT8MIN    0
#define UINT8MAX    255
#define SINT16MIN   -32768
#define SINT16MAX   32767
#define UINT16MIN   0
#define UINT16MAX   32767
#define UINT32MIN   0
#define UINT32MAX   4294967295
#define SINT32MIN   -2147483648
#define SINT32MAX   2147483647
/***************** BIT define ***************/
#define iBIT0       0x0001
#define iBIT1       0x0002
#define iBIT2       0x0004
#define iBIT3       0x0008
#define iBIT4       0x0010
#define iBIT5       0x0020
#define iBIT6       0x0040
#define iBIT7       0x0080
#define iBIT8       0x0100
#define iBIT9       0x0200
#define iBIT10      0x0400
#define iBIT11      0x0800
#define iBIT12      0x1000
#define iBIT13      0x2000
#define iBIT14      0x4000
#define iBIT15      0x8000

#define SETBIT(BIT) ((BIT)=(1))
#define CLRBIT(BIT) ((BIT)=(0))

#define TSTBIT(BIT) ((BIT))

#define StartTimer(timername,timecounter) ((timername)=(timecounter))
#define CheckTimer(timername) (((timername)==0)?1:0)

#define MIN(a,b) ((a>b)?b:a)
#define MAX(a,b) ((a>b)?a:b)

#define TRUE                       1
#define FALSE                      0

#endif  /* HEADER_H */

