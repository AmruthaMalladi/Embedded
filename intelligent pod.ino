
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

//buzz
int Buzzer = 4;

//pir
int ledPin = 13;                
int inputPin = 2;               
int pirState = LOW;             
int val = 0; 

//ir
const int irsensor=4;
const int LED=2;
int stats=0;

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

  //pir
  pinMode(ledPin, OUTPUT);      
  pinMode(inputPin, INPUT); 

  //buzz
    pinMode (Buzzer, OUTPUT);
  
  //servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); 

  //ir
  pinMode(LED, OUTPUT);
  pinMode(irsensor, INPUT);

   //servo
  Serial.print("Testing servo Motor...");
  servo90();
  delay(1500);
  servo0();
  delay(1500);
  
  buzz();
  delay(2000);

  pir();
  delay(2000);

  //ir
  Serial.print("Testing ir...");
  ir();
  delay(2000);

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

  Firebase.setFloat("ir",stats);  
if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
 }}

 void buzz(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);
  digitalWrite (Buzzer, LOW);  //turn buzzer off
  delay(1000);
}

void pir(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
 void loop(){
  
 }
