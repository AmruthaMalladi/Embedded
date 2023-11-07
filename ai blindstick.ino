

const int relay1 = 28;
const int relay2 = 27;
const int pump = 26;

//ultra
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

//soil
#define SoilPin 4

//temp
#include "DHTesp.h"
#define DHTpin 15    
DHTesp dht;


//dc
const int motor1Pin1 = 25; 
const int motor1Pin2 = 27;
const int motor2Pin1 = 32; 
const int motor2Pin2 = 33;
const int enable1Pin = 14; 
const int enable2Pin = 12;
String movement= "";
String  Command= "";


void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(pump, OUTPUT);
  dht.setup(DHTpin, DHTesp::DHT11);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
   pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  //dc
  Serial.print("Testing DC Motor...");
  forward();
  delay(3000);
  stop();
  delay(3000);
  backward();
  delay(3000);
  stop();
  delay(3000);
  left();
  delay(3000);
   stop();
  delay(3000);
  right();
  delay(1500);
   stop();
  delay(1500);

  relay1_on();
  delay(5000);
  relay1_off();
  delay(5000);
  
  relay2_on();
  delay(5000);
  relay2_off();
  delay(5000);
  
  pump_on();
  delay(5000);
  pump_off();
  delay(5000);
  
  soil();
  delay(2000);
  
  temp();
  delay(2000);

  ultra();
  delay(2000);
}

void relay1_on() {
  digitalWrite(relay1, HIGH);
  Serial.println("Current flowing");
  } 
void relay1_off() { 
  digitalWrite(relay1, LOW);
  Serial.println("current not flowing");
} 
void relay2_on() { 
  digitalWrite(relay2, HIGH);
  Serial.println("current not flowing");
}
void relay2_off() { 
  digitalWrite(relay2, LOW);
  Serial.println("current not flowing");
}
void pump_on() { 
  digitalWrite(pump, HIGH);
  Serial.println("pump on");
}
void pump_off() { 
  digitalWrite(pump, LOW);
  Serial.println("pump off");
}
void soil(){
  float sensorValue = analogRead(SoilPin);
  Serial.println(sensorValue);
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

void left(){
//  digitalWrite(enable1Pin, HIGH); 
//  digitalWrite(enable2Pin, HIGH);
//  Serial.println("Moving left");
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
//  digitalWrite(enable1Pin, LOW);
//  digitalWrite(enable2Pin, LOW);
 }
 
 void stop(){
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);
 }
 
 void right(){
//  digitalWrite(enable1Pin, HIGH);
//  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving right");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);
//  digitalWrite(enable1Pin, LOW);
//  digitalWrite(enable2Pin, LOW);
 }
 
  void forward(){
//  digitalWrite(enable1Pin, HIGH);
//  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving front");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
//  digitalWrite(enable1Pin, LOW);
//  digitalWrite(enable2Pin, LOW);
 }
 
  void backward(){
//  digitalWrite(enable1Pin, HIGH);
//  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving back");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);
//  digitalWrite(enable1Pin, LOW);
//  digitalWrite(enable2Pin, LOW); 
 }

 void ultra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
}

void loop(){
  temp();
  delay(1000);

  //ultra
  ultra();
  if (distance<=20){
  stop();
  delay(1000);
  }
}
