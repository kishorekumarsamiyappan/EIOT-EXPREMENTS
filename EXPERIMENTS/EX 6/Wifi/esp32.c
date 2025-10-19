#include <Arduino.h> 
#include <Wire.h> 
#include "Adafruit_SHT31.h" 
#include <WiFi.h> 
#include <WiFiMulti.h> 
#include <HTTPClient.h> 
#define USE_SERIAL Serial 
 
bool enableHeater = false;
uint8_t loopCnt = 0; 
 
Adafruit_SHT31 sht31 = Adafruit_SHT31(); 
WiFiMulti wifiMulti; 
 
void setup() { 
Serial.begin(9600); 
while (!Serial) 
   	 delay(10);     // will pause Zero, Leonardo, etc until serial console opens 
 
  Serial.println("SHT31 test"); 
 	 if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr 
 	   Serial.println("Couldn't find SHT31"); 
 	   while (1) delay(1); 
  } 
 
 	 USE_SERIAL.begin(115200); 
 
  USE_SERIAL.println(); 
  USE_SERIAL.println(); 
  USE_SERIAL.println(); 
	 
  for (uint8_t t = 4; t > 0; t--) { 
 	   USE_SERIAL.printf("[SETUP] WAIT %d...\n", t); 
  	  USE_SERIAL.flush(); 
   	 delay(1000); 
 	 } 
 
  	wifiMulti.addAP("OnePlus Nord 4", "123456789"); 
} 
 
void loop() { 
 // wait for WiFi connection 
  char buf[300]; 
 	 if ((wifiMulti.run() == WL_CONNECTED)) { 
 
   	 HTTPClient http; 
 
   	 USE_SERIAL.print("[HTTP] begin...\n"); 
  	  // configure traged server and url 
  	  //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS 
 
 	 float t = sht31.readTemperature(); 
  	float h = sht31.readHumidity(); 
 
sprintf(buf,"https://api.thingspeak.com/update?api_key=HARZP4QU1ZOIO2EA&field1=%f&field2=%f",t,h); 
 
   	 http.begin(buf);  //HTTP 
 	   USE_SERIAL.print("[HTTP] GET...\n"); 
   	 // start connection and send HTTP header 
  	  int httpCode = http.GET(); 
 
 	   // httpCode will be negative on error 
 	   if (httpCode > 0) { 
 	     // HTTP header has been send and Server response header has been handled 
  	    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode); 
 
   	   // file found at server 
    	  if (httpCode == HTTP_CODE_OK) { 
      	  String payload = http.getString(); 
    	    USE_SERIAL.println(payload); 
  	    } 
 	 } else { 
 	     USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", 
http.errorToString(httpCode).c_str()); 
 	   } 
    http.end(); 
  } 
  delay(5000); 
}
