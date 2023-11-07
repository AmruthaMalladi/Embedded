//buzzer
const int buzzer = 9;

//relay
const int RELAY_PIN = 3; 

//gas
int Gas_analog = A0;

//ir
const int irSensor=8;
const int LED=13;
int stats = 0;

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(5,6);

//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Wire.h>
const int analogIn = A6;

void setup(){
  //baud rate
  Serial.begin(115200);

  //ir
  pinMode(LED, OUTPUT);          
  pinMode(irSensor,INPUT); 

  //buzzer
  pinMode(buzzer, OUTPUT);

   //relay
  pinMode(RELAY_PIN, OUTPUT);

  //gsm
  delay(1000);
  gsm.begin(9600);

  //lcd
  lcd.init();                      
  lcd.begin(16,2);

  buzz();
  delay(1000);
  relay();
  delay(3000);
  gas();
  delay(2000);
  SendMessage();
  delay(1000);
  ir();
  delay(2000);
}

void buzz(){
  tone(buzzer, 1000); 
  delay(1000);       
  noTone(buzzer);              
}

void relay() {
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println ( "relay on" ) ;
  delay(3000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println ( "relay off" ) ;
}

void gas(){
 int gassensorAnalog = digitalRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
 delay(2000);
  lcd.setCursor(0,0);
  lcd.print("gas");
  lcd.print(gassensorAnalog);
  delay(2000);
}

void SendMessage()
{
  gsm.println("AT+CMGF=1"); 
  delay(1000);  
  gsm.println("AT+CMGS=\"+917975528296\"\r"); 
  delay(1000);
  gsm.print("hi");
  gsm.println((char)26);
  delay(1000);
}

void ir()
{
  stats = digitalRead(irSensor);
  if(stats == HIGH)  
  {
    digitalWrite(LED, HIGH);  
    Serial.println("irSensorhigh");
    lcd.setCursor(0,1);
    lcd.print("motion");
    delay(2000);
  }
  else
  {
    digitalWrite(LED, LOW);    
    Serial.println("irsensorlow");
    lcd.setCursor(0,1);
    lcd.print("no motion");
    delay(2000);
  }

}

void loop(){
  
}
