int Gas_analog135 = 4;
int Gas_analog4 = 32;
int Gas_analog2 = 33;

#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17);

void setup(){
gsm.begin(9600);
Serial.begin(115200);
gas135();
delay(2000);
gas4();
delay(2000);
gas2();
delay(2000);
SendMessage();
delay(1000);
}
void gas135(){
 int gassensorAnalog = analogRead(Gas_analog135);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
}
void gas4(){
 int gassensorAnalog = analogRead(Gas_analog4);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
}
void gas2(){
 int gassensorAnalog = analogRead(Gas_analog2);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
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
void loop(){
  
}
