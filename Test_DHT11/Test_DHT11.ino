
/*
NodeMCU DHT11 TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/

#include "DHT.h"  

#define DHTPIN 2     // Digital pin connected to the DHT sensor (D4)
#define DHTTYPE DHT11    // Select DHT type

DHT dht(DHTPIN,DHTTYPE);  

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Serial.print('\n');
  Serial.println("DHT11 Temperature and Humidity ");
  delay(100);
}

void loop()
{
  float h = dht.readHumidity();
  float tc = dht.readTemperature();
  
  Serial.print('\n');                 // Read the temperature and humidity per two sec
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.print("%,  ");
  Serial.print("Temperature = ");
  Serial.print(tc);
  Serial.print("°C, ");
  delay(2000);            
}
