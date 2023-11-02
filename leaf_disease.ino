//dht
#include "DHTesp.h"
#define DHTpin A0
#define SensorPin A0
DHTesp dht;


const int relay0 = 14;//d5 of 8266
const int relay1 = 12;
const int relay2 = 13;
const int relay3 = 15;

int count;
char input[12];

void setup()
{
  
  Serial.begin(115200);// baud rate
  Serial.println();

  dht.setup(DHTpin, DHTesp::DHT11);
  pinMode(relay0, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  temp();
  delay(2000);
  re0();
  delay(2000);
  re1();
  delay(2000);
  re2();
  delay(2000);
  re3();
  delay(2000);  
  soil();
  delay(2000);
}

void temp()
{
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
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

void re0()
{
  digitalWrite(relay0, HIGH);
  Serial.println("Current Flowing");
  delay(2000); 
  digitalWrite(relay0, LOW);
  Serial.println("Current not Flowing");
  delay(2000);
}
void re1() {
  digitalWrite(relay1, HIGH);
  Serial.println("Current Flowing");
  delay(2000); 
  digitalWrite(relay1, LOW);
  Serial.println("Current not Flowing");
  delay(2000);
}
void re2() {
  digitalWrite(relay2, HIGH);
  Serial.println("Current Flowing");
  delay(2000); 
  digitalWrite(relay2, LOW);
  Serial.println("Current not Flowing");
  delay(2000);
}
void re3() {
  digitalWrite(relay3, HIGH);
  Serial.println("Current Flowing");
  delay(2000); 
  digitalWrite(relay3, LOW);
  Serial.println("Current not Flowing");
  delay(2000);
}
void soil() {
  float sensorValue = analogRead(SensorPin);
  Serial.print("Moisture content");
  Serial.println(sensorValue);
  delay(2000);
}
void loop()
{
  temp();
  delay(2000);
  soil();
  delay(2000);
//  if(Serial.available()>0)
//   {
//    count=0;
//    while(Serial.available() && count < 12)
//    {
//      input[count]= Serial.read();
//       count++;
//       delay(5);    }

  if(Serial.available()>0){
  switch(Serial.read())
  {
    case '1':
    break;

    case '2':
    break;
  }
   }
}
