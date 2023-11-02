//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
//change
#define FIREBASE_HOST "hhhf-c29cd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MQZyMpanhNR1yxeHiJX8F0itsLwc7dJUTODkS1sN"
#define WIFI_SSID "OPPO A5 2020"
#define WIFI_PASSWORD "qwertyuiop"

// ultrasonic
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

//temperature
const int sensor=36;
float vout;
float tempc;
float tempf;

//gas sensor
int Gas_analog = 34;

//TDS sensor
int TDS_analog = 32; // tds gpio27

//relay 1
const int relay1 = 25;//relay gpio26

//relay 2
const int relay2 = 26;//relay gpio26

//buzzer
int Buzzer = 27;

//waterflow sensor
#define LED_BUILTIN 12
#define SENSOR  13
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}
float price=0;
String bill_paid="";


void setup() 
{
   Serial.begin(115200); // Starts the serial communication

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
  Firebase.set("Command", 0);
  Firebase.set("FB1", 0);

  
  //ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 
 

//relay1
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  
//buzzer
  pinMode (Buzzer, OUTPUT);

 //waterflow sensor
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

Serial.println("start");

 ultra();
 delay(2000);
 temp();
 delay(2000);
 gas();
 delay(2000);
 tds();
 delay(2000);
 relay1_on();
 delay(2000);
 relay1_off();
 delay(2000);
 relay2_on();
 delay(2000);
 relay2_off();
 delay(2000);
 buzz_on();
 delay(2000);
 buzz_off();
 delay(2000);
 waterf();
 delay(2000);
 }


  //ultrasonic sensor
 void ultra ()
 {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
  Firebase.setFloat("distance",distance);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
 }

//temperature sensor
 void temp() {
vout= analogRead(sensor);
Serial.println(vout);
vout= (vout*500)/4095;
tempc= vout;
tempf=(vout*1.8)+32;
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
Serial.print("in Fahrenheit=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();
delay (1000);
 Firebase.setFloat("temp",tempc);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
 }

//gas sensor
 void gas(){
  int gassensorAnalog = analogRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
 delay(2000);
  Firebase.setFloat("gas",gassensorAnalog);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
}

//tds sensor
void tds() {
  float sensorValue = analogRead(TDS_analog);
   Serial.println("tds sensorValue");
  Serial.println(sensorValue);
  delay(2000);
 Firebase.setFloat("tds",sensorValue);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
  
}

//relay 1
void relay1_on() {
  digitalWrite(relay1, HIGH);
  Serial.println("water pumping");}
  
void relay1_off(){
  digitalWrite(relay1, LOW);
  Serial.println("water not pumping");
  }

//relay 2
void relay2_on() {
  digitalWrite(relay2, HIGH);
  Serial.println("water pumping");
} 
void relay2_off(){
  digitalWrite(relay2, LOW);
  Serial.println("water not pumping");
  
}

//buzzer
void buzz_on(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
}
void buzz_off(){
  digitalWrite (Buzzer, LOW);  //turn buzzer off
 
}


//water flow sensor
void waterf() {
   currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;

    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;

     Firebase.setFloat("totalMilliLitres",totalMilliLitres); 
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
  }
}
void water_read(){
 totalMilliLitres=0;
 Firebase.setFloat("totalMilliLitres",totalMilliLitres);  
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 Firebase.setFloat("price",price);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
 waterf();
 if  (totalMilliLitres > 10){
 price=price+1;
 Firebase.setFloat("price",price);
 if (Firebase.failed()) {
 Serial.print("setting /number failed:");
 Serial.println(Firebase.error());  }
 delay(1000); 
 }
}

void loop(){
 temp(); 
 water_read();
bill_paid= Firebase.getString("bill_paid");
Serial.println(bill_paid);
if (bill_paid== "yes"){
  totalMilliLitres=0;
  price=0;
  water_read();
  delay(1000); 
}}
