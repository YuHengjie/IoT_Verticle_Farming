/*
NodeMCU BH1750/DHT11 TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/

#include <Wire.h>   // BH1750
#include <BH1750.h>
BH1750 lightMeter;


#include "DHT.h"  
#define DHTPIN 2     // Digital pin connected to the DHT sensor (D4)
#define DHTTYPE DHT11    // Select DHT type
DHT dht(DHTPIN,DHTTYPE); 


void setup(){
  Serial.begin(9600);
  
  dht.begin();
  Wire.begin();         
  lightMeter.begin();        // lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE): default mode
  Serial.print('\n');
  Serial.println(F("BH1750/DHT11 Test begin"));
  
}

void loop() {
  float lux = lightMeter.readLightLevel();
  float h = dht.readHumidity();
  float tc = dht.readTemperature();
  

  Serial.print("Light = ");
  Serial.print(lux);
  Serial.print(" lx,  ");
  
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.print(" %,  ");
  
  Serial.print("Temperature = ");
  Serial.print(tc);
  Serial.print(" °C.");

  Serial.print("\n");

  delay(2000);
}
