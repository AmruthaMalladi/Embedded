//current
#define Current_sensor A0  
float i;

//buzz
const int buzzer = 9; 

//voltage
const int voltageSensor = A1;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

//lcd
#include "LiquidCrystal.h"
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

void setup() {

Serial.begin(9600);
pinMode(Current_sensor, INPUT);
pinMode(buzzer, OUTPUT);

lcd.begin(16,2);
lcd.print(" Measure > 25V  ");
delay(2000);

current();
delay(1000);
buzz();
delay(1000);
volt();
delay(1000);
}

void current() {
  i = analogRead(Current_sensor);
  Serial.println("current");
  Serial.println(i); 
  lcd.setCursor(0,1);
  lcd.print("curr =         ");
  lcd.setCursor(9,0);
  lcd.print(vIN);
  delay(500);                
}

 void buzz(){
 
 tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  
}

void volt()
{
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("Input = ");
  Serial.println(vIN);
  lcd.setCursor(0,0);
  lcd.print("Volt =         ");
  lcd.setCursor(9,0);
  lcd.print(vIN);
  delay(500);
  
}
void loop(){
  
}
