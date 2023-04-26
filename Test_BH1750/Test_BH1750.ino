/*
NodeMCU BH1750 TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup(){
  Serial.begin(9600);

  Wire.begin();         
  lightMeter.begin();        // lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE): default mode
  Serial.print('\n');
  Serial.println(F("BH1750 Test begin"));
  
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(2000);
}
