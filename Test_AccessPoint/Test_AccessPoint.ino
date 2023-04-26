
/*
NodeMCU Access Point TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/
 
#include <ESP8266WiFi.h>        
 
const char *ssid = "DigitalTwin";     // Set WiFi network name
const char *password = "FarmingTest"; // Set WiFi password 
                                      // No internet access

void setup() {
  Serial.begin(9600);              // Set the data rate in bits per second (baud) for serial data transmission
 
  WiFi.softAP(ssid, password);     // WiFi.softAP for access point model of NodeMCU
  
  Serial.print("\n");
  Serial.print("WiFi SSID: ");    
  Serial.println(ssid);              
  Serial.print("IP address: ");      
  Serial.println(WiFi.softAPIP());  
}
 
void loop() { 
}
