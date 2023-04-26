
/*
NodeMCU Wireless Station TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/
 
#include <ESP8266WiFi.h>        
 
const char* ssid     = "DigitalTwinNetwork"; // Fill WiFi network name     
const char* password = "FarmingTest";        // Fill WiFi password  

                                            
void setup() {
  Serial.begin(9600);         
  
  WiFi.begin(ssid, password);                  // Connect to WiFi
  Serial.print("\n");
  Serial.print("Connecting to ");              
  Serial.print(ssid); Serial.println(" ...");  
  
  int i = 0;                                   // Test if WiFi connection is successful 
  while (WiFi.status() != WL_CONNECTED) {      // The return value of WiFi.status() is determined by the connection status
    delay(1000);                               // If successful, return WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // Check every one second
  }                                            // Print the wait time
                                        
  Serial.println("");                          // If successful, print connection information
  Serial.println("Connection established!");   
  Serial.print("NodeMCU IP address:    ");     // And the IP address of NodeMCU    
  Serial.println(WiFi.localIP());              // Use PC to ping the IP address to test (PC connects to same WiFi)
}
 
void loop() {                                   
}
