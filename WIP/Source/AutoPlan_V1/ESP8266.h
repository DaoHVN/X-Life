#ifndef ESP8266_H
#define ESP8266_H

#if ((WIFI_CONTROL == ENABLE) && (WIFI_MODE == iESP8266))
#define ANDROID_MODE    1
#define WEB_MODE        2
#define SR_MODE         ANDROID_MODE

#define ESP8266_RX_PIN  2
#define ESP8266_TX_PIN  3

#define ESP8266_BAUDRATE_DEFAULT    115200
#define ESP8266_BAUDRATE            9600

extern void ESP8266_Hard_Init(void);
extern void ESP8266_Soft_Init(void);
extern void ESP8266_cal(void);

#endif  /* WIFI_CONTROL == ENABLE */

#endif  /* ESP8266_H */

