
#include <ESP32Servo.h>
Servo myservo;
int pos = 0; 
int servoPin = 13;

int vib_pin=7;
int led_pin=2;

const int relay = 26;

const int PushButton=15;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);   
  myservo.attach(servoPin, 500, 2400);

  int vib_pin=7;
  int led_pin=2;

  pinMode(relay, OUTPUT);

  pinMode(PushButton, INPUT);

  servo90();
  delay(100);
  servo0();
  delay(100);
  vib();
  delay(2000);
  relay_on();
  delay(5000);
  relay_off();
  delay(5000); 
  push_button();
  delay(1000); 

}
void servo90(){
   myservo.write(90);     
}

 void servo0(){
   myservo.write(0);     
}

void vib() {
  int val;
  val=digitalRead(vib_pin);
  if(val==1)
  {
    digitalWrite(led_pin,HIGH);
    Serial.println("vibration");
    delay(1000);
    digitalWrite(led_pin,LOW);
    delay(1000);
   }
   else
   digitalWrite(led_pin,LOW);
   Serial.println("no vibration");
}

void relay_on(){
   digitalWrite(relay, HIGH);
  Serial.println("Current flowing");
}

void relay_off(){
   digitalWrite(relay, LOW);
  Serial.println("Current not flowing");
}

void push_button(){
  int Push_button_state = digitalRead(PushButton);
  Serial.println(Push_button_state);
}

void loop() {
 
}
