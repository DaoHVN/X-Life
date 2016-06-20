#ifndef PREDEFINE_H
#define PREDEFINE_H

#define ENABLE                  1
#define DISABLE                 0

/* Cpu type define */
#define iATMEGA328P             1
#define iATMEGA8                2
#define CPU_TYPE                iATMEGA328P

                
/* Simulator debug */
#define SIM_DEBUG               ENABLE
#define SIM_DEBUG_BAUDRATE      9600

/* Fail Safe control */
#define FAILSAFE_CONTROL        ENABLE

/* Analog control */
#define ADC_CONTROL             ENABLE

/* Real time control */
#define TIME_CONTROL            ENABLE
#define iDS1307                 1
#define TIME_MODE               iDS1307

/* Relay output control */
#define RELAY_CONTROL           ENABLE
#define RELAY_NUMBER            2

/* Wireless control */
#define WIFI_CONTROL            DISABLE
#define iESP8266                1
#define WIFI_MODE               iESP8266

/* Display Control */
#define DISPLAY_CONTROL         ENABLE
#define iNOKIA5110              1
#define iLCD16X02               2
#define iLCD16X04               3
#define iLCD20X02               4
#define iLCD20X04               5
#define DISPLAY_MODE            iLCD16X02

/* Temporate Control */
#define TEMP_CONTROL            DISABLE
#define iDHT11                  1
#define iDHT22                  2
#define TEMP_MODE               iDHT11

/* Key Board Control */
#define KEYBOARD_CONTROL        ENABLE
#define iNUMKEY                 4
#define i74LS165                1
#define iPARALEL                2
#define iMATRIX                 3
#define KEYBOARD_MODE           iPARALEL

/* EEPROM control */
#define EEPROM_CONTROL          ENABLE
#define iINTERNAL               1
#define EEPROM_MODE             iINTERNAL

#endif  /* PREDEFINE_H */

