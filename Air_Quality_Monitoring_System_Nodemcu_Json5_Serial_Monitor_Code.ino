
#include <ESP8266WiFi.h>
#include "ArduinoJson.h"
#include <SoftwareSerial.h> 

SoftwareSerial s_serial_to_nano(2,0); 

const char *ssid =  "Punith V ";     
const char *pass =  "Punith@2628";

WiFiClient client;

float mq2_value_global;
float mq4_value_global;
float mq5_value_globak;
float mq135_value_global;
float t_global;
float h_global;
float Pressure_global;
float Altitude_global;

int Wifi_Led = 14;

void setup() {

  Serial.begin(9600);
      
  Serial.println("-------------------------");
  Serial.println("  AIR QUALITY MONITORING SYSTEM ");
  Serial.println("-------------------------");

  pinMode(Wifi_Led, OUTPUT);
  digitalWrite(Wifi_Led, LOW);

 Serial.println("Connecting to ");
 Serial.println(ssid); 
 
 WiFi.begin(ssid, pass); 
 while (WiFi.status() != WL_CONNECTED) 
 { 
  delay(500);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected"); 
 digitalWrite(Wifi_Led, HIGH);
 s_serial_to_nano.begin(4800);

}

void loop() {
  
  if (s_serial_to_nano.available()) {
 DynamicJsonBuffer jsonBuffer(1024); 
 JsonObject& root = jsonBuffer.parseObject(s_serial_to_nano);
if(!root.success()){
  return;
}
JsonArray& data = root["data"];


float mq2_value = root["mq2_value"];
float mq4_value = root["mq4_value"];
float mq5_value = root["mq5_value"];
float mq135_value = root["mq135_value"];
float t = root["t"];
float h = root["h"];

int Pressure = root["Pressure"];
int Altitude = root["Altitude"];

 
 Serial.println();
 Serial.print("1. Smoke ");Serial.print(mq2_value);Serial.println(" PPM");
 Serial.print("2. cng ");Serial.print(mq4_value);Serial.println(" PPM");
 Serial.print("3. lpg ");Serial.print(mq5_value);Serial.println("PPM");
 Serial.print("4. airquality ");Serial.print(mq135_value);Serial.println(" PPM");
 Serial.print("5. temperature ");Serial.print(t);Serial.println(" C");
 Serial.print("6. humidity ");Serial.print(h);Serial.println(" %");
 Serial.print("7. Pressure ");Serial.print(Pressure);Serial.println(" PA");
 Serial.print("8. Altitude ");Serial.print(Altitude);Serial.println(" M");
 Serial.println();

 while (s_serial_to_nano.available() > 0)
 s_serial_to_nano.read();

}
}
