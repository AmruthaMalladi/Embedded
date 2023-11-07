
//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
//CHANGE
#define FIREBASE_HOST "hhhf-c29cd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MQZyMpanhNR1yxeHiJX8F0itsLwc7dJUTODkS1sN"
#define WIFI_SSID "OPPO A5 2020"
#define WIFI_PASSWORD "qwertyuiop"

//lcd
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Wire.h>

//servo
#include <ESP32Servo.h>
int pos = 0;
Servo myservo;
const int servoPin = 4;

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17); 

//gas
float Gas_analog = 34;
float gassensor=0;

//buzzer
int Buzzer = 2;

void setup(){
Serial.begin(115200);
Serial.println("start");
//firebase

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 delay(200);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  delay(200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //lcd
lcd.init();
lcd.begin(16,2);
lcd.backlight();//Power on the back light

  //buzzer
  pinMode (Buzzer, OUTPUT);

  //servo
//  ESP32PWM::allocateTimer(0);
//  ESP32PWM::allocateTimer(1);
//  ESP32PWM::allocateTimer(2);
//  ESP32PWM::allocateTimer(3);
//  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400);

  //gsm
  delay(1000);
  gsm.begin(9600);
  

  
  gasvalue();
  delay(2000);
  servo90();
  delay(1500);
  servo0();
  delay(1500);
  buzzeron();
  delay(2000);
  buzzeroff();
  delay(2000);
  SendMessage();
  delay(1000);
}

  
void gasvalue(){
  float gassensor= analogRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensor);

   delay(2000);
  lcd.setCursor(0,0);
  lcd.print("gas");
  lcd.print(gassensor);
 delay(2000);
  
  Firebase.setFloat("gas value", gassensor);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
      }
}
 void servo90(){
  myservo.write(90); 
   Serial.println("90 degree");// tell servo to go to position in variable 'pos'
    delay(1500);
 }
 void servo0(){
    myservo.write(0);
    Serial.println("0 degree");// tell servo to go to position in variable 'pos'
    delay(1500);
 }
 void buzzeron(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);}
  
  void buzzeroff(){
  digitalWrite (Buzzer, LOW);  //turn buzzer off
  delay(1000);
}
void SendMessage()
{
  gsm.println("AT+CMGF=1"); 
  delay(1000);  
  gsm.println("AT+CMGS=\"+917975528296\"\r"); 
  delay(1000);
//  gsm.println(e);
// delay(100);
 gsm.print("alert");
 gsm.println((char)26);
  delay(1000);
}
 
void loop(){
gasvalue();
 float gassensor= analogRead(Gas_analog);
  if(gassensor>=200){
    servo90();
    buzzeron();
    SendMessage();
    Firebase.setFloat("alert", gassensor);
    delay(2000);   
  lcd.setCursor(0,1);
  lcd.print("alert");
  delay(2000);  
  }
    lcd.clear();
    servo0();
    buzzeroff();
 
}
