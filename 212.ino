const int relay = 5;

int Buzzer = 4;

#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17);

void setup() {
  Serial.begin(115200);

  delay(1000);
  gsm.begin(9600);
  
  pinMode(relay, OUTPUT);
  
  pinMode(Buzzer, OUTPUT);

  relay_command_on();
  delay(2000);
  relay_command_off();
  delay(2000);
  buzz_on();
  delay(1000);
  buzz_off();
  delay(1000);
  SendMessage();
  delay(1000);
}

void relay_command_on(){
  digitalWrite(relay, LOW);
  Serial.println("Current Flowing");
}
void relay_command_off(){
  digitalWrite(relay, HIGH);
  Serial.println("Current not Flowing");
}
void buzz_on(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);
}
void buzz_off(){
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
  delay(1000);
}
void loop(){
  
}
