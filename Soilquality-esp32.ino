 #include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);
int TDS_analog = 27; // tds gpio27
#define SensorPin 4  // soil gpio4
const int relay = 26;//relay gpio26
#include "DHTesp.h"
#define DHTpin 15
int Gas_analog = 2;//gas gpio 2
float vout;
float tempc;
float tempf;
DHTesp dht;
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  dht.setup(DHTpin, DHTesp::DHT11); 
  pinMode(relay, OUTPUT);
  temp();
  delay(1000);
  oled();
  delay(1000);
  pumprelay();
  delay(3000);
  gas();
  delay(2000);
  soil();
  delay(2000);
  tds();
  delay(2000);
}
void temp() {
delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
}
void oled() {
 
  display.init();
  display.drawString(0, 0, "");
  display.display();

}
void pumprelay() {
  
  digitalWrite(relay, HIGH);
  Serial.println("water pumping");
  delay(2000); 
  digitalWrite(relay, LOW);
  Serial.println("water not pumping");
  
}  
void gas(){
  int gassensorAnalog = analogRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
 delay(2000);
}
void soil() {
  float sensorValue = analogRead(SensorPin);
  Serial.println("soilmoisture Value");
  Serial.println(sensorValue);
  
}
void tds() {
  float sensorValue = analogRead(TDS_analog);
   Serial.println("tds sensorValue");
  Serial.println(sensorValue);
  delay(2000);
}
void loop(){}
