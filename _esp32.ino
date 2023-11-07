//esp cam, ir, ir-temp, alcohol, relay, l293d-dc, ultra

//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
//change
#define FIREBASE_HOST "hhhf-c29cd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MQZyMpanhNR1yxeHiJX8F0itsLwc7dJUTODkS1sN"
#define WIFI_SSID "OPPO A5 2020"
#define WIFI_PASSWORD "qwertyuiop"

#define MQ3pin 13     
float sensorValue;

// ultrasonic
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

//relay 1
const int relay1 = 25;//relay gpio26

//dc
const int motor1Pin1 = 25; 
const int motor1Pin2 = 27;
const int motor2Pin1 = 32; 
const int motor2Pin2 = 33;
const int enable1Pin = 14; 
const int enable2Pin = 12;
String movement= "";
String  Command= "";


//ir
const int irsensor=4;
const int LED=2;
int stats=0;  

//relay
const int relay = 26;

void setup() {
 Serial.begin(115200); // Starts the serial communication

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

  //relay
  pinMode(relay, OUTPUT);

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

  //ir
  Serial.print("Testing ir...");
  ir();
  delay(2000);

  //ultra
  Serial.print("Testing ultra...");
  ultra();
  delay(3000);

  //alcohol
  Serial.println("MQ3 warming up!");
  delay(2000);
  alcl();
  delay(2000);

  //relay
  Serial.println("relay");
  relayon();
  delay(5000);
  relayoff();
  delay(5000);
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

 void alcl() {
  sensorValue = analogRead(MQ3pin); 
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  delay(2000); 
}

void relayon(){ 
  digitalWrite(relay, HIGH);
  Serial.println("Current flowing");
}

void relayoff(){ 
  digitalWrite(relay, LOW);
  Serial.println("Current not flowing");
}

void loop() {

}
