//relay
int led_pin = 13 ;
const int RELAY_PIN = 3; 

//servo
#include<Servo.h>
Servo Myservo;
int pos;

//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Wire.h>

//vibration
int vib_pin=7;

//soil
int SensorPin= 4;

//ldr
float light4=A0;
float light1=A1;
float light2=A2;
float light3=A3;

void setup(){
  //baud rate
  Serial.begin(115200);

  //lcd
  lcd.init();                      
  lcd.begin(16,2);

  //servo
Myservo.attach(12);

  //vibration
  pinMode(vib_pin,INPUT);
  pinMode(led_pin,OUTPUT);

 //relay
  pinMode(RELAY_PIN, OUTPUT);

  pump_on();
  delay(3000);
  pump_off();
  delay(3000);
  vib();
  delay(2000);
  soil();
  delay(2000);
  servo0();
  delay(3000);
  servo30();
  delay(3000);
  servo60();
  delay(3000);
  servo90();
  delay(3000);
  servo0();
  delay(3000);  
  ldr1();
  delay(2000);
  ldr2();
  delay(2000);
  ldr3();
  delay(2000);
  ldr4();
  delay(2000);
}

void vib() {
  int val;
  val=digitalRead(vib_pin);
  if(val==1)
  {
    digitalWrite(led_pin,HIGH);
    Serial.println ( "vibration on" ) ;
    digitalWrite(led_pin,LOW);
     lcd.setCursor(0,0);
     lcd.print("vib_mode");
    delay(1000);
    digitalWrite(led_pin,LOW);
    Serial.println ( "vibration off" ) ;
    delay(1000);
   }
   else
   digitalWrite(led_pin,LOW);
}

void pump_on() {
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println ( "water pumping" ) ;}
  
void pump_off() {
  digitalWrite(RELAY_PIN, LOW);
  Serial.println ( "water not pumping" ) ;
}

void ldr1(){
  light1 = analogRead(A0);
  Serial.println("ldr1_Value"); 
  Serial.print(light1, DEC); 
  Serial.print(" \n"); 
  lcd.setCursor(0,1);
  lcd.print("ldr1");
  lcd.print(light1);
  delay(2000);
  lcd.clear();
}
void ldr2(){
  light2 = analogRead(A0);
  Serial.println("ldr2_Value"); 
  Serial.print(light2, DEC); 
  Serial.print(" \n"); 
  lcd.setCursor(0,1);
  lcd.print("ldr2");
  lcd.print(light2);
  delay(2000);
  lcd.clear();
}
void ldr3(){
  light3 = analogRead(A0);
  Serial.println("ldr3_Value"); 
  Serial.print(light3, DEC); 
  Serial.print(" \n"); 
  lcd.setCursor(0,1);
  lcd.print("ldr3");
  lcd.print(light3);
  delay(2000);
  lcd.clear();
}
void ldr4(){
  light4= analogRead(A0);
  Serial.println("ldr4_Value"); 
  Serial.print(light4, DEC); 
  Serial.print(" \n"); 
  lcd.setCursor(0,1);
  lcd.print("ldr4");
  lcd.print(light4);
  delay(2000);
  lcd.clear();
}

void soil(){
  float sensorValue = digitalRead(SensorPin);
  Serial.println("Soil_Value");
  Serial.println(sensorValue);
  if (sensorValue== LOW){
    pump_on();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("moist low");
  lcd.setCursor(0,1);
  lcd.print("pump on");
  delay(2000);}
   if (sensorValue== HIGH){
    pump_off();
    lcd.clear();
  }

}


void servo0() {
    Myservo.write(0); 
    Serial.println("0 degree");   
    delay(3000);}
void servo30() {
    Myservo.write(30); 
    Serial.println("30 degree");   
    delay(3000);}
void servo60() {
    Myservo.write(60); 
    Serial.println("60 degree");   
    delay(3000);}  
void servo90() {
    Myservo.write(90); 
    Serial.println("90 degree");   
    delay(3000);}      

void loop(){
if (light1> light2 && light1> light3 && light1> light4){
  servo0();
}

if (light2> light1 && light2> light3 && light2> light4){
  servo30();
}

if (light3> light2 && light3> light1 && light3> light4){
  servo60();
}

if (light4> light2 && light4> light1 && light4> light3){
  servo90();
}
vib();
delay(2000);
soil();
delay(2000);
ldr1();
delay(2000);
ldr2();
delay(2000);
ldr3();
delay(2000);
ldr4();
delay(2000);

}
