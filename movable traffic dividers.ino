//heart
int sensorPin = A0;                                
float sensorValue = 0;                             
int count = 9;
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;

float ecg_count=0;

//temp
const int lm35_pin = A1;

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(1,0);

//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Wire.h>

void setup() {
Serial.begin(115200);

lcd.init();                      
lcd.begin(16,2);
lcd.backlight();

gsm.begin(9600);
  
pinMode(10, INPUT); // Setup for leads off detection LO +
pinMode(11, INPUT); // Setup for leads off detection LO -

pinMode (13, OUTPUT); 


 ecg();
 delay(2000);
 heart();
 delay(2000);
 temp();
 delay(1000);
 SendMessage();
 delay(1000);
}
 
void ecg() {
 
if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
Serial.println('!');
delay(2000);
}
else{
// send the value of analog input 2:
ecg_count=analogRead(A2);
Serial.println("ecg");
Serial.println(ecg_count);
}
//Wait for a bit to keep serial data from saturating
delay(2000);
 lcd.setCursor(0,1);
 lcd.print("ecg");
 lcd.print(ecg_count);
 delay(2000);
 lcd.clear();
}
void heart(){
  starttime = millis();
while (millis()<starttime+10000)                   // Reading pulse sensor for 10 seconds
{
sensorValue = analogRead(sensorPin);
if (sensorValue > 550 && counted == false)  // Threshold value is 550 (~ 2.7V)
{
count++;
Serial.print ("count = ");
Serial.println (count);
digitalWrite (13,HIGH);
delay (50);
digitalWrite (13, LOW);
counted = true;
}
else if (sensorValue < 550)
{
counted = false;
digitalWrite (13, LOW);
}
}
heartrate = count*6;                               // Multiply the count by 6 to get beats per minute
Serial.println ();
Serial.print ("BPM = ");
Serial.println (heartrate);                        // Display BPM in the Serial Monitor
Serial.println ();
count = 0;
lcd.setCursor(0,0);
lcd.print("bpm");
lcd.print(heartrate);
}


void temp(){
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  lcd.setCursor(0,0);
  lcd.print("TempinC");
  lcd.print(temp_val);
  delay(2000);
  lcd.clear();
}
void SendMessage()
{
  gsm.println("AT+CMGF=1"); 
  delay(1000);  
  gsm.println("AT+CMGS=\"+917975528296\"\r"); 
  delay(1000);
  gsm.print("alert");
  
  gsm.println((char)26);
  delay(1000);
}

void loop(){
  temp();
  delay(2000);
  
  
}
