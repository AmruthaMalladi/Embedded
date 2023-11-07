
//relay
const int relay = 26;

//buzzer
int Buzzer = 1;

//ldr with led
int ldrsensor;
const int LED=2;

//noise
int noise_digital = 36;

//servo
#include <ESP32Servo.h>
Servo myservo;
int servoPin = 13;

//smoke-mq2
int Gas_analog = 4;

//temp dht11
#include "DHTesp.h"
#define DHTpin 15 
DHTesp dht;

//moisture
#define moistPin 12

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17);  //16 brown


void setup() {
Serial.begin(115200);
  //servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);   
  myservo.attach(servoPin, 500, 2400);
  //relay
  pinMode(relay, OUTPUT);
  //buzz
  pinMode (Buzzer, OUTPUT);
  //led
  pinMode(LED, OUTPUT);           
  pinMode(ldrsensor,INPUT); 
  //gsm
  delay(1000);
  gsm.begin(9600);
  //temp
  dht.setup(DHTpin, DHTesp::DHT11);

  fan();
  delay(5000);
  buzz();
  delay(1000);
  ldr();
  delay(1000);
  noise();
  delay(2000);
  servo90();
  delay(100);
  smoke();
  delay(2000);
  temp();
  delay(2000);
  SendMessage();
  delay(1000);
  moist();
  delay(2000);
}

void fan() {
  digitalWrite(relay, LOW);
  Serial.println("fan off");
  digitalWrite(relay, HIGH);
  Serial.println("fan on");
  delay(5000);
}

void buzz(){
  digitalWrite (Buzzer, HIGH); 
  delay(1000);
  digitalWrite (Buzzer, LOW); 
}
 
void ldr()
{
  ldrsensor = analogRead(A0);
  Serial.print(ldrsensor, DEC); 
   if( ldrsensor== HIGH)     
  {
    digitalWrite(LED, HIGH);  
    Serial.println("dark");
    delay(2000);
  }
  else
  {
    digitalWrite(LED, LOW);    
    Serial.println("light");
    delay(2000);
  } 
 
}

void noise(){
 int vol_digital = digitalRead(noise_digital);
 Serial.print("\t");
 Serial.println(vol_digital);
}

void servo(){
  myservo.write(90);  
  delay(15);
  myservo.write(0);
}

void smoke(){
 int gassensorAnalog = analogRead(Gas_analog);
 Serial.println("smoke sensor");
 Serial.println(gassensorAnalog);
}

void temp(){
  Serial.println();
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
 void SendMessage()
{
  gsm.println("AT+CMGF=1"); 
  delay(1000);  
  gsm.println("AT+CMGS=\"+917975528296\"\r"); 
  delay(1000);
  gsm.print("hi");
  gsm.println((char)26);
  delay(1000);
}

void moist() {
  float moistValue = analogRead(moistPin);
  Serial.println(moistValue);
}


void loop(){
  
} 
