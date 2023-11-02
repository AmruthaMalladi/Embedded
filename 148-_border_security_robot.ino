//pir                
int inputPin = 2;               
int pirState = LOW;             
int val = 0;                    
 
//temp
#include "DHTesp.h"
#define DHTpin 15
DHTesp dht;

//dc
const int motor1Pin1 = 27; 
const int motor1Pin2 = 26;
const int motor2Pin1 = 25; 
const int motor2Pin2 = 33;
const int enable1Pin = 14; 
const int enable2Pin = 12;
int value1=5, value=10;

//ultra
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

//ir
const int irsensor=4;
const int LED=2;
int stat=0;  

//gas
int Gas_analog = 34;
 void setup() {
  
Serial.println();

 // sets the pins as outputs:
pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(motor2Pin1, OUTPUT);
pinMode(motor2Pin2, OUTPUT);
pinMode(enable1Pin, OUTPUT);
pinMode(enable2Pin, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(irsensor, INPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);
pinMode(19, OUTPUT);
pinMode(3, INPUT);
pinMode(inputPin, INPUT);
  
Serial.begin(115200);
 
 // testing
 Serial.print("Testing DC Motor...");


dht.setup(DHTpin, DHTesp::DHT11);

  
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
  ir();
  delay(2000);
  ultra();
  delay(3000);
  gas();
  delay(1500);
  temp();
  delay(2000);
  pir();
  delay(2000); 
}
void pir(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(LED, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

 void forward(){
  digitalWrite(enable1Pin, HIGH); 
  digitalWrite(enable2Pin, HIGH);

  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
   digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  delay(2000);
   digitalWrite(enable1Pin, LOW);
   
   digitalWrite(enable2Pin, LOW);
 }
 void stop(){
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  
  delay(1000);
 }
 void backward(){
  
  digitalWrite(enable1Pin, HIGH);
  
  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
  digitalWrite(enable1Pin, LOW);   
  digitalWrite(enable2Pin, LOW);
  
 }
  void left(){
  
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving left");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(enable2Pin, LOW);
  
 }
  void right(){
  
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving right");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(enable2Pin, LOW);
  
 }

 void ir(){
  stat= digitalRead(irsensor);
  if (stat==HIGH)
  {digitalWrite(LED, HIGH);
  Serial.println("irsensor is high");
}
 else
 {
  
  digitalWrite(LED, LOW);
  Serial.println("irsensor is low");
 }
 }
 
 void ultra(){
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
 
 void gas(){
   int gassensorAnalog = analogRead(Gas_analog);
   Serial.print("Gas Sensor: \n");
   Serial.print(gassensorAnalog);
   
 }
 void temp(){
  Serial.println("\nStatus\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
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
void loop() {

 
if( value1==0)
 {
    forward();
    delay(2000);
   
  }
  if( value1==1)
 {
     stop();
    delay(1000);
  }
  if(value1==2)
  {
    backward();
    delay(2000);
  } }
