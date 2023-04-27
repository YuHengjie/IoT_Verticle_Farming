/*
NodeMCU WebServer for sensors TEST
By Hengjie Yu (https://github.com/YuHengjie)
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>   // BH1750
#include <BH1750.h>

const char* ssid = "DigitalTwinNetwork";  // Fill WiFi network name    
const char* password = "FarmingTest";     // Fill WiFi password 

#define DHTPIN 2     // Digital pin connected to the DHT sensor (D4)
#define DHTTYPE DHT11    // Select DHT type
DHT dht(DHTPIN,DHTTYPE); 

BH1750 lightMeter;

float l = 0.0;
float t = 0.0;
float h = 0.0;


AsyncWebServer server(80);  // Create AsyncWebServer object on port 80

unsigned long previousMillis = 0;    // Store last time DHT was updated

const long interval = 6000;  // Updates DHT data every 6 seconds

// Can learn the html at https://www.w3schools.com/
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html lang="en">  
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="style.css">
  <script src="https://kit.fontawesome.com/3c7f5e0f61.js" crossorigin="anonymous"></script>
  <title> IoT verticle farming </title>
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .lth-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>

<body>
  <h2>Light-Temperature-Humidity Monitor</h2>
  <p>
    <i class="far fa-sun" style="color:#ffd700;"></i> 
    <span class="lth-labels">Light</span>
    <span id="light">%LIGHT%</span>
    <sup class="units">lux</sup>
  </p>
  <p>
    <i class="fas fa-thermometer-quarter" style="color:#daa520;"></i> 
    <span class="lth-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fa-solid fa-droplet" style="color:#00bfff;"></i> 
    <span class="lth-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>

<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("light").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/light", true);
  xhttp.send();
}, 6000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 6000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 6000 ) ;


</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String(l);
}

void setup(){
  Serial.begin(9600);
  dht.begin();
  Wire.begin(); 
  lightMeter.begin();
  
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


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });
  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(l).c_str());
  });
  
  // Start server
  server.begin();
}
 
void loop(){  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    
    // Read light as lux 
    float newL = lightMeter.readLightLevel();
    if (isnan(newL)) {
      Serial.println("Failed to read from BH1750 sensor!");
    }
    else {
      l = newL;
      Serial.println(l);
    }
    
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
}
