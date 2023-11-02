#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include "MAX30100_PulseOximeter.h"

#define FIREBASE_HOST "ismart-d75d8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "0jkWwQQXpSxdcag38JQxfMrAmoWk5sxyWDDqFr8E"
#define WIFI_SSID "jayanth"                                     // input your home or public wifi name 
#define WIFI_PASSWORD "1234567890"

float temp_val = 0;
float tempC = 0;
long duration;
int distance;
int stat1 = 0;

//ir sensor
const int irsensor = 32;

//ultrasonic
const int trigPin = 26;
const int echoPin = 25;

//relay
const int relay1 = 21;
const int relay2 = 14;

//temperature
const int analogIn = 35;

//alcohol sensor
const int alch_analog = 33;

float sensorValue;//connect the ADC 13 pin t
int RawValue = 0;
float Voltage = 0;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  
  delay(1000);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(200);
  pinMode(analogIn, INPUT);
  pinMode(alch_analog, INPUT);
  pinMode(irsensor, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  delay(1000);
  pinMode(relay1, OUTPUT);
  delay(1000);
  pinMode(relay2, OUTPUT);
  delay(1000);
  
  ir();
  delay(1000);
  
  ultra();
  delay(1000);
  
  pump();
  delay(1000);
  
  doorlock();
  delay(1000);

}

//ir sensor
void ir()
{
  stat1 = digitalRead(irsensor);
  if (stat1 == HIGH)
  {

    Serial.println("irsensor is Low");

  }
  else
  {

    Serial.println("irsensor is High");
    pump();
    alch() ;
  }
}

//Ultrasonic
void ultra() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
  if (distance < 10)
  {
    Serial.println("Please maintain Social Distance");
    delay(1000);
  }
  Firebase.setFloat("Distance", distance);
  delay(1000);
}

//pump
void pump()
{
  Serial.println("Relay1 is ON ");
  delay(1000);
  digitalWrite(relay1, HIGH);
  delay(1000);
  digitalWrite(relay1, LOW);
  delay(1000);
}
//alcohol
void alch()
{
  int gassensorAnalog = analogRead(alch_analog);
  Serial.println("gasssensor");
  Serial.println(gassensorAnalog);
  delay(1000);
  if (gassensorAnalog > 1500)
  {
    Serial.println("Sanitization is DONE, Proceed");
    Firebase.setString("Status", "Sanitization is DONE, Proceed");
    delay(1000);
  }
  else
  {
    Serial.println("Alert..Sanitization is Not DONE");
    Firebase.setString("Status", "Sanitization is NOT DONE, Door will not open");
    delay(1000);
  }
}

//doorlock
void doorlock()
{
  Serial.println("Relay2 is ON ");
  digitalWrite(relay2, HIGH);
  delay(1000);
  digitalWrite(relay2, LOW);
  delay(1000);
}

void loop()
{
  ultra();
  ir();
  delay(1000);
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 2048.0) * 3300;
  tempC = Voltage * 0.1;
  Serial.println("\t Temperature in C = ");
  Serial.println(tempC, 1);

  delay(1000);
  if (tempC < 42)
  {
    Serial.println("temp normal");
    delay(1000);
    Firebase.setString("Status", "Temperature normal, Proceed");
    delay(1000);
   Firebase.setFloat("Temp", tempC);
  delay(1000);

   int gassensorAnalog = analogRead(alch_analog);
  Serial.println("gasssensor");
  Serial.println(gassensorAnalog);
  delay(1000);
  if (gassensorAnalog > 1500)
  {
    Serial.println("Sanitization is DONE, Proceed");
    Firebase.setString("Status", "Sanitization is DONE, Proceed");
    delay(1000);

  if (Serial.available() > 0) {
    switch (Serial.read())
    {
      case '1':
        Serial.println("Mask Not wearing");
        delay(1000);
        Firebase.setString("Status", "Mask Not wearing");
        delay(1000);
        break;

      case '0':
        Serial.println("Mask  wearing");
        delay(1000);
        Firebase.setString("Status", "Mask  wearing");
        delay(1000);
        doorlock();
        break;
    }
  }
  }
    Serial.println("Sanitization is NOT DONE, terminate");
    Firebase.setString("Status", "Sanitization is NOT DONE,terminate");
    delay(1000);
  }
    Serial.println("temp high");
    delay(1000);
    Firebase.setString("Status", "Temperature high");
    delay(1000);
  }
  
