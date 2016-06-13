#include "HEADER.h"
#include "PREDEFINE.h"
#include "TIMER.h"
#include "ESP8266.h"

#if ((WIFI_CONTROL == ENABLE) && (WIFI_MODE == iESP8266))
#include <SoftwareSerial.h>
/*************************************************************************************************/
/* Global Define Serial UART PORT */
SoftwareSerial esp8266(ESP8266_RX_PIN,ESP8266_TX_PIN);

/************************************* sendCommandtoESP8266 ***************************************/
/* send Command Data to ESP8266 */
/* Call : --- */
/* Input: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no) */
/* Returns: The response from the esp8266 (if there is a reponse) */
/**************************************************************************************************/
static String sendCommandtoESP8266(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
#if SIM_DEBUG == ENABLE
    if(debug)
    {
      Serial.print(response);
    }
#endif    
    return response;
}
/************************ sendCIPData *****************************/
/*
* Name: sendCIPDATA
* Description: sends a CIPSEND=<connectionId>,<data> command
*
*/
static void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommandtoESP8266(cipSend,1000,SIM_DEBUG);
   sendCommandtoESP8266(data,1000,SIM_DEBUG);
}
/************************ sendHTTPResponse *****************************/
/*
* Name: sendHTTPResponse
* Description: Function that sends HTTP 200, HTML UTF-8 response
*/
static void sendHTTPResponse(int connectionId, String content)
{
     
     // build HTTP response
     String httpResponse;
     String httpHeader;
     // HTTP Header
     httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"; 
     httpHeader += "Content-Length: ";
     httpHeader += content.length();
     httpHeader += "\r\n";
     httpHeader +="Connection: close\r\n\r\n";
     httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
     sendCIPData(connectionId,httpResponse);
}
/************************ ESP8266_HardInit *****************************/
void ESP8266_Hard_Init(void)
{
#if SIM_DEBUG == ENABLE
  Serial.begin(9600);
#endif
  /* Init baudrate first time for connect ESP8266 */
  esp8266.begin(ESP8266_BAUDRATE_DEFAULT);
  /* reset module */
  sendCommandtoESP8266("AT+RST\r\n",2000,SIM_DEBUG);  
  /* Change Baud to 9600 */                       
  sendCommandtoESP8266("AT+CIOBAUD=9600\r\n",2000,SIM_DEBUG);   
  /* reinstall ESP baudrate */
  esp8266.begin(ESP8266_BAUDRATE);
  /* reset module */                                       
  sendCommandtoESP8266("AT+RST\r\n",2000,SIM_DEBUG);
#if SR_MODE == ANDROID_MODE
   /* configure as access point STA */
  sendCommandtoESP8266("AT+CWMODE=1\r\n",1000,SIM_DEBUG);                   
#else
   /* configure as access point AP */
  sendCommandtoESP8266("AT+CWMODE=1\r\n",1000,SIM_DEBUG);                   
#endif
  /* connect to Wifi */
  sendCommandtoESP8266("AT+CWJAP=\"Xlife\",\"0984999892\"\r\n",5000,SIM_DEBUG);  
  delay(5000);
  /* get ip address */
  sendCommandtoESP8266("AT+CIFSR\r\n",1000,SIM_DEBUG);         
  /* configure for multiple connections */              
  sendCommandtoESP8266("AT+CIPMUX=1\r\n",1000,SIM_DEBUG);       
  /* turn on server on port 80 */             
  sendCommandtoESP8266("AT+CIPSERVER=1,80\r\n",1000,SIM_DEBUG);              
#if SIM_DEBUG == ENABLE
  Serial.println("Server Ready");
#endif
}
/************************ ESP8266_SoftInit *****************************/
void ESP8266_Soft_Init(void)
{
  StartTimer(tU08_WifiWaitTime, 600); /* 600 * 100ms = 60000 ms = 60 sec */
}
/************************ ESP8266_cal *****************************/
void ESP8266_cal(void)
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    if(esp8266.find("+IPD,"))
    {
      if( /*CheckTimer(tU08_WifiWaitTime) || */1)
      {
       // get the connection id so that we can then disconnect
       int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                             // the ASCII decimal value and 0 (the first decimal number) starts at 48     
       if(esp8266.find("pin=")) /* goto string PIN */
       {
#if (SIM_DEGUG == ENABLE)        
        Serial.println("file pin"); // advance cursor to "pin="
#endif        
       }
  
       int pinNumber = (esp8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
       pinNumber += (esp8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
       
       digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin    
       
       // build string that is send back to device that is requesting pin toggle
       String content;
       content = "Pin ";
       content += pinNumber;
       content += " is ";
       
       if(digitalRead(pinNumber))
       {
         content += "ON";
       }
       else
       {
         content += "OFF";
       }
       
       sendHTTPResponse(connectionId,content);
       
       // make close command
       String closeCommand = "AT+CIPCLOSE="; 
       closeCommand+=connectionId; // append connection id
       closeCommand+="\r\n";
       
       sendCommandtoESP8266(closeCommand,1000,SIM_DEBUG); // close connection
      } /* CheckTimer(tU08_WifiSerialWait) */
    }
  }
  else  /* esp8266.available() */
  {
    StartTimer(tU08_WifiWaitTime,10);
  } 
}

#endif  /* WIFI_CONTROL == ENABLE */


