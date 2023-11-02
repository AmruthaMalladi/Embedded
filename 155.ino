#include <Servo.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(1,0);

//MQ2
int Gas_analog2 = A0;

//MQ135
int Gas_analog135 = A1;

//SERVO MOTOR
int servoPin = 9;
Servo servo;

//buzz
int Buzzer = 10;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);


void setup(){
Serial.begin(115200);

gsm.begin(9600);

servo.attach(servoPin);

pinMode (Buzzer, OUTPUT);

lcd.init();
lcd.backlight();
serv();
delay(2000);
MQ2();
delay(2000);
MQ135();
delay(2000);
buzz();
delay(1000);
SendMessage();
delay(1000);



}
void serv(){
servo.write(90);
Serial.println("90 degree");
delay(2000);
servo.write(0);
Serial.println("0 degree");
}

void MQ2(){
int gassensor2= analogRead(Gas_analog2);
 Serial.println("gasssensorMQ2");
 Serial.println(gassensor2); 

 lcd.setCursor(0, 0); 
 lcd.print("MQ2: ");
 lcd.print(gassensor2);
}

void MQ135(){
int gassensor135= analogRead(Gas_analog135);
 Serial.println("gasssensorMQ135");
 Serial.println(gassensor135);

 lcd.setCursor(0, 1); 
 lcd.print("MQ135: ");
 lcd.print(gassensor135);
}

void buzz(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);
  digitalWrite (Buzzer, LOW);  //turn buzzer off
  delay(1000);
}

void SendMessage()
{
 gsm.println("AT+CMGF=1"); 
 delay(1000);  
 gsm.println("AT+CMGS=\"+917975528296\"\r"); 
 delay(1000);
 gsm.print("hi");
 gsm.println((char)26);
} 

void loop()
{
  }
