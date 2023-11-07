//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Wire.h>

//temp
const int analogIn = A6;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

//ldr
int ldrsensorValue;

//buzzer
int Buzzer = 4;

//soil moisture
#define SoilPin 36

//pump
const int pump = 26;

//fan
const int fan = 27;

//light
const int light = 25;

void setup(){
Serial.println("start");

//lcd
lcd.init();                      
lcd.begin(16,2);

//buzzer
pinMode (Buzzer, OUTPUT);

//pump
pinMode(pump, OUTPUT);

//fan
pinMode(fan, OUTPUT);

//light
pinMode(light, OUTPUT);

Serial.begin(115200);

temp();
delay(2000);
ldr();
delay(2000);
buzzeron();
delay(1000);
buzzeroff();
delay(1000);
soil();
delay(2000);
pump_on();
delay(5000);
pump_off();
delay(5000);
fan_on();
delay(5000);
fan_off();
delay(5000);
light_on();
delay(5000);
light_off();
delay(5000);
}

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
  lcd.setCursor(0,0);
  lcd.print("TempinC");
  lcd.print(tempC);
  lcd.setCursor(0,1);
  lcd.print("Temp in F");
  lcd.print(tempF);
  lcd.clear();
}

void ldr(){
  ldrsensorValue = analogRead(A3); // read analog input pin 0
  Serial.print(ldrsensorValue, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers
  delay(1000); // wait 100ms for next reading
  lcd.setCursor(0,0);
  lcd.print("ldr");
  lcd.print(ldrsensorValue);
  lcd.clear();
}

void buzzeron(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
}

void buzzeroff(){
  digitalWrite (Buzzer, LOW); //turn buzzer off
}

void soil(){
  float soilValue = analogRead(SoilPin);
  Serial.println(soilValue);
}
void pump_on(){
  digitalWrite(pump, HIGH);
  Serial.println("water pumping");
}

void pump_off(){
  digitalWrite(pump, LOW);
  Serial.println("water not pumping");
}

void fan_on(){
  digitalWrite(fan, HIGH);
  Serial.println("fan on");
}

void fan_off(){
  digitalWrite(fan, LOW);
  Serial.println("fan off");
}

void light_on(){
  digitalWrite(light, HIGH);
  Serial.println("light on");
}

void light_off(){
  digitalWrite(light, LOW);
  Serial.println("light off");
}

void loop(){
  
}
