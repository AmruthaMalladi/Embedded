//temp
#include <dht.h>
#define dht_apin A0 // A0 pin of arduino directly 
dht DHT;

//fire
int led_pin = 13 ;
int flame_sensor_pin = 8 ;
int flame_pin = HIGH ;

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(1,0);

//buzzer
const int buzzer = 9;

//relay
const int RELAY_PIN = 3; 

//vibration
int vib_pin=7;
 
void setup(){
  //baud rate
  Serial.begin(115200);

  //vibration
  pinMode(vib_pin,INPUT);
  pinMode(led_pin,OUTPUT);

  //buzzer
  pinMode(buzzer, OUTPUT);

  //gsm
  delay(1000);
  gsm.begin(9600);

  //fire
  pinMode ( led_pin , OUTPUT );
  pinMode ( flame_sensor_pin , INPUT );

 //relay
  pinMode(RELAY_PIN, OUTPUT);

  temp();
  delay(5000);
  fire();
  delay(2000);
  SendMessage();
  delay(1000);
  buzz();
  delay(1000); 
  pump();
  delay(3000);
  vib();
  delay(2000);

}

void temp(){
    Serial.println("DHT11 Humidity & temperature Sensor\n\n");
    delay(1000);
    DHT.read11(dht_apin);   
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");  
}

void fire ( ) {
flame_pin = digitalRead ( flame_sensor_pin ) ; 
if (flame_pin == LOW ) 
{
Serial.println ( " FLAME , FLAME , FLAME " ) ;
digitalWrite ( led_pin , HIGH ) ;
delay(2000);
}
else
{
Serial.println ( " no flame " ) ;
digitalWrite ( led_pin , LOW ) ;
}}

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

void buzz(){
  tone(buzzer, 1000); 
  delay(1000);       
  noTone(buzzer);              
}

void pump() {
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println ( "water pumping" ) ;
  delay(3000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println ( "water not pumping" ) ;
}

void vib() {
  int val;
  val=digitalRead(vib_pin);
  if(val==1)
  {
    digitalWrite(led_pin,HIGH);
    delay(1000);
    digitalWrite(led_pin,LOW);
    delay(1000);
   }
   else
   digitalWrite(led_pin,LOW);
}

void loop(){
  
}
