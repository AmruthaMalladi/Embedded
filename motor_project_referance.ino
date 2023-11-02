//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
//change
#define FIREBASE_HOST "hhhf-c29cd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MQZyMpanhNR1yxeHiJX8F0itsLwc7dJUTODkS1sN"
#define WIFI_SSID "OPPO A5 2020"
#define WIFI_PASSWORD "qwertyuiop"

//servo
#include <ESP32Servo.h>
int pos = 0;
Servo myservo; 
const int servoPin = 13;


//dc
const int motor1Pin1 = 25; 
const int motor1Pin2 = 27;
const int motor2Pin1 = 32; 
const int motor2Pin2 = 33;
const int enable1Pin = 14; 
const int enable2Pin = 12;
String movement= "";
String  Command= "";

//ultra
const int trigPin = 16;
const int echoPin = 17;
long duration;
float distance;

//ir
const int irsensor=4;
const int LED=2;
int stats=0;  

//gas
int Gas_analog = 39;

 //temp
const int analogIn = A6;
int RawValue= 0;
float Voltage = 0;
float tempC = 0;
float tempF = 0;
 
void setup() {
  //firebase
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 delay(200);
 
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
 
  delay(200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("Command", 0);
  Firebase.set("FB1", 0);

  
  //servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); 

 // dc
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  //ir
  pinMode(LED, OUTPUT);
  pinMode(irsensor, INPUT);
   
  //ulta 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(19, OUTPUT);
  pinMode(3, INPUT);
  

 
  Serial.begin(115200);
  Serial.println("start");

  // testing
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

  //servo
  Serial.print("Testing servo Motor...");
  servo90();
  delay(1500);
  servo0();
  delay(1500);

  //ir
  Serial.print("Testing ir...");
  ir();
  delay(2000);

  //ultra
  Serial.print("Testing ultra...");
  ultra();
  delay(3000);

  //gas
  Serial.print("Testing gas...");
  gas();
  delay(1500);

  //temp
  Serial.print("Testing temp");
  temp();
  delay(1000);

 
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
 
 
 void servo90(){
  myservo.write(90); 
  Serial.println("90 degree");// tell servo to go to position in variable 'pos'
  delay(1500);
 }
 
 void servo0(){
    myservo.write(0);
    Serial.println("0 degree");// tell servo to go to position in variable 'pos'
    delay(1500);
 }
 
 void ir(){
  stats= digitalRead(irsensor);
  if (stats==HIGH)
  {digitalWrite(LED, HIGH);
  Serial.println("irsensor is high");
 }
 else
 {
  digitalWrite(LED, LOW);
  Serial.println("irsensor is low");
 }}
 
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
   Firebase.setFloat("distance",distance); 
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
 }
 
 void gas(){
   float gassensorAnalog = analogRead(Gas_analog);
   Serial.print("Gas Sensor: ");
   Serial.print(gassensorAnalog);
   Firebase.setFloat("gas",gassensorAnalog);  
   if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }}
  
 
void temp(){
 RawValue = analogRead(analogIn);
Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
tempC = Voltage * 0.1;
tempF = (tempC * 1.8) + 32; // conver to F
Serial.print("Raw Value = " ); // shows pre-scaled value
Serial.print(RawValue);
Serial.print("\t milli volts = "); // shows the voltage measured
Serial.print(Voltage,0); //
Serial.print("\t Temperature in C = ");
Serial.print(tempC,1);
Serial.print("\t Temperature in F = ");
Serial.println(tempF,1);
delay(500);
Firebase.setFloat("temperature",tempC);  
if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }

}
 
void loop() {

  
  //lcd
  gas();
  delay(1500);
  temp();
  delay(1000);

  //ir
  ir();
  if (stats==LOW){
    servo90();
    delay(1000);
    temp();
    delay(1000);
    servo0();
    delay(1000);
  }

  //ultra
  ultra();
  if (distance<=20){
  stop();
  delay(1000);
  }
 // app button
  Serial.println( Firebase.getString("movement"));
  movement= Firebase.getString("movement");
  Serial.println("motor");
  Serial.println(movement);
  delay(1000);
  if(movement=="1"){
    forward();
    delay(1000);
    stop();
  }
  if(movement=="2"){
    backward();
    delay(1000);
    stop();
  }
  if(movement=="4"){
    right();
    delay(1000);
    stop();
  }
  if(movement=="3"){
    left();
    delay(1000);
    stop();
  }
  if(movement=="5"){
    stop();
    delay(1000);


  }
  

   //voice command
  Serial.println( Firebase.getString("Command"));
  Command= Firebase.getString("Command");
  Serial.println(Command);
  Command.remove(0, 2);
  Command.remove(5, 7);
  Serial.println(Command);
  delay(1000);
  
  if(Command=="front"){
    forward();
    delay(1000);
    stop();
  }
  
  if(Command=="back "){
     backward();
    delay(1000);
    stop();
  }
  if(Command=="left "){
    left();
    delay(1000);
    stop();
  }
  if(Command=="right"){
    right();
    delay(1000);
    stop();
  } 
   if(Command=="stop "){
    stop();
    delay(1000);
  }
  
}
 
 
  
  
