//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Wire.h>
//ultra
const int trigPin = 16;// 16gpio of esp32
const int echoPin = 17;// 17gpio of esp32
long duration;
int distance;
//relay
const int relay = 26;// GPIO26 of esp32
//buzz
int Buzzer = 4;//gpio4 of esp32
//alcl
#define MQ3pin 13 //connect the ADC 13 pin t 
float sensorValue;//connect the ADC 13 pin t
//temp
const int analogIn = A6;//34gpio of esp32 or adc6 of esp32- temp
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;
//ir
const int irSensor=2;//17gpio of esp32
const int LED=2;//2gpio of esp32
int stat = 0;


void setup() {
Serial.begin(115200);
//lcd
lcd.init(); 
lcd.begin(16,2);
lcd.backlight();

//ulta
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);

//relay 
pinMode(relay, OUTPUT);

//ir
pinMode(LED, OUTPUT);           
pinMode(irSensor,INPUT); 

//buzz
pinMode (Buzzer, OUTPUT);


ultra();
delay (2000);
 temp();
delay(1000);
 relay_pump_on();
delay(2000);
 relay_pump_off();
delay(2000);
ir();
delay(2000);
 buzz_on();
delay(3000);
 buzz_off();
delay(3000);
 alcl();
delay(2000);

}
void ultra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
   
  lcd.setCursor(0, 0);
  lcd.print("Dis");
  lcd.print(distance);
  delay(2000);
}
void temp(){
RawValue = analogRead(analogIn);
Voltage = (RawValue / 2048.0) * 3300; 
tempC = Voltage * 0.1;
tempF = (tempC * 1.8) + 32; 
Serial.print("Raw Value = " ); 
Serial.print(RawValue);
Serial.print("\t milli volts = ");
Serial.print(Voltage,0); //
Serial.print("\t Temperature in C = ");
Serial.print(tempC,1);
Serial.print("\t Temperature in F = ");
Serial.println(tempF,1);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("TempinC");
lcd.print(tempC);
delay(2000);
lcd.setCursor(0,1);
lcd.print("TempinF");
lcd.print(tempF);
delay(2000);
}
void relay_pump_on(){
digitalWrite(relay, HIGH);
Serial.println("water filling");}
 void relay_pump_off(){
digitalWrite(relay, LOW);
Serial.println("water not filling");
} 
void ir(){
stat = digitalRead(irSensor);
if(stat == HIGH)     //Check the sensor output
{
 digitalWrite(LED, HIGH);   // set the LED on
 Serial.println("irSensorhigh");
 lcd.clear();
 lcd.print("no person");
 
 delay(2000);
}
else
{
 digitalWrite(LED, LOW);   
 Serial.println("irsensorlow");

 
 lcd.print("person detected");
 lcd.clear();
}}
void buzz_on(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);}
 void buzz_off(){ 
  digitalWrite (Buzzer, LOW);  //turn buzzer off
  delay(1000);
}
void alcl(){
 // Serial.println("MQ3 warming up!");
  delay(2000);
  sensorValue = analogRead(MQ3pin); 
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
}
void loop(){
  ir ();
  if(stat == LOW){
    buzz_on() ;
  }
}
