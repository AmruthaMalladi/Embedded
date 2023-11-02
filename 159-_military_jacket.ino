//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#define FIREBASE_HOST "military-73e51-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "vlydBZnoV5Gq4RszurCXSFv0zJeQg3Kb08k43YNv"
//change
#define WIFI_SSID "abishek" //hotspot id
#define WIFI_PASSWORD "mnjaac12" // hotspot password
#include "DHTesp.h"

//gps
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial GPS_SoftSerial(18,19);
TinyGPSPlus gps;      
volatile float minutes, seconds;
volatile int degree, secs, mins;

//metal
int metal_analog = 26;

//gas
int Gas_analog = 25;

//buttons
const int PushButton1=15;
const int PushButton2=21;
const int PushButton3=2;

//heart
int sensorPin = 27;                                
float sensorValue = 0;                             
int count = 9;
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;

//led
int ledpin= 5;
String  Authority= "";

//temp
#define DHTpin 12

    
DHTesp dht;

//adxl
const int xpin = 33; // x-axis of the accelerometer
const int ypin = 34; // y-axis
const int zpin = 35; // z-axis

void setup(){
  Serial.begin(115200);
  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Firebase.setString("wifi", "wifi connected");
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
  

//temp
dht.setup(DHTpin, DHTesp::DHT11); 
delay(dht.getMinimumSamplingPeriod());

//button
pinMode(PushButton1, INPUT);  
pinMode(PushButton2, INPUT); 
pinMode(PushButton3, INPUT); 

//gps
GPS_SoftSerial.begin(9600);

temp();
delay(2000);
metal();
delay(2000);
adxl();
delay(3000);
gas ();
delay(2000);
heart();
delay(2000);
button1();
delay(2000);
button2();
delay(2000);
button3();
delay(2000);
led();
delay(2000);
location();
delay(2000);

}

void location() {
        smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
        hr_val = gps.time.hour(); /* Get hour */
        min_val = gps.time.minute();  /* Get minutes */
        sec_val = gps.time.second();  /* Get seconds */
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(lat_val, 6);
          Serial.print("Latitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
          DegMinSec(lng_val); /* Convert the decimal degree value into degrees minutes seconds form */
          Serial.print("Longitude in Decimal Degrees : ");
          Serial.println(lng_val, 6);
          Serial.print("Longitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
        }
        if (!alt_valid)
        {
          Serial.print("Altitude : ");
          Serial.println("*****");
        }
        else
        {
          Serial.print("Altitude : ");
          Serial.println(alt_m_val, 6);    
        }
        if (!time_valid)
        {
          Serial.print("Time : ");
          Serial.println("*****");
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d/%02d/%02d \n", hr_val, min_val, sec_val);
          Serial.print(time_string);    
        }
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}


void test_case(){
  int x_test = digitalRead(xpin);
  int y_test = digitalRead(ypin);
  int z_test = digitalRead(zpin);
if(x_test== HIGH && y_test==HIGH && z_test==HIGH){
   Serial.println("adxl working");
  Firebase.setString("adxl_test", "working");}
  

  int heart_test= digitalRead(sensorPin);
  if(heart_test== HIGH){
   Serial.println("heart_sensor working");
  Firebase.setString("heartsensor_test", "working");}  

  
  int gas_test= digitalRead(Gas_analog);
  if(gas_test== HIGH){
   Serial.println("heart_sensor working");
  Firebase.setString("gassensor_test", "working");}  

  int temp_test= digitalRead(DHTpin);
  if(temp_test== HIGH){
   Serial.println("temp_sensor working");
  Firebase.setString("tempsensor_test", "working");}  

  int metal_test= digitalRead(metal_analog);
  if(metal_test== HIGH){
   Serial.println("metal_sensor working");
  Firebase.setString("metalsensor_test", "working");}  
}


void button1(){
int Push_button1_state = digitalRead(PushButton1);
if ( Push_button1_state == HIGH )
{ 
 Serial.println("enemies ahead");
  Firebase.setString("button1", "enemies ahead");
  Firebase.remove("button2");
  Firebase.remove("button3");
}
}

void button2(){
int Push_button2_state = digitalRead(PushButton2);
if ( Push_button2_state == HIGH )
{ 
 Serial.println("explosives found");
  Firebase.setString("button2", "explosives found");
  Firebase.remove("button1");
  Firebase.remove("button3");
}
}

void button3(){
int Push_button3_state = digitalRead(PushButton3);
if ( Push_button3_state == HIGH )
{ 
 Serial.println("need medical assistance");
  Firebase.setString("button3", "need medical assistance");
  Firebase.remove("button2");
  Firebase.remove("button1");
}
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
count = count*6; // Multiply the count by 0.5 to get beats per minute
heartrate = count/15;
Serial.println ();
Serial.print ("BPM = ");
Serial.println (heartrate); 

 Firebase.setFloat("heartrate",heartrate);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
 
}

void temp()
{
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float temp2ft = dht.toFahrenheit(temperature);

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
Firebase.setFloat("Humidity",humidity);  
Firebase.setFloat("Temperature",temperature);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void metal(){
 float metalsensorAnalog = analogRead(metal_analog);
 Serial.println("metal_sensor");
 Serial.println(metalsensorAnalog);
 delay(2000);

 Firebase.setFloat("metal",metalsensorAnalog);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void adxl()
{
int x = analogRead(xpin); //read from xpin
delay(1); //
int y = analogRead(ypin); //read from ypin
delay(1);
int z = analogRead(zpin); //read from zpin
Serial.println("x: ");
Serial.println(x);
Serial.println("y: ");
Serial.println(y);
Serial.println("z: ");
Serial.println(z);

//float zero_G = 512.0; //ADC is 0~1023 the zero g output equal to Vs/2
//float scale = 102.3; //ADXL335330 Sensitivity is 330mv/g
////330 * 1024/3.3/1000
//Serial.print(((float)x - 331.5)/65*9.8); //print x value on serial monitor
//Serial.print("\t");
//Serial.print(((float)y - 329.5)/68.5*9.8); //print y value on serial monitor
//Serial.print("\t");
//Serial.print(((float)z - 340)/68*9.8); //print z value on serial monitor
//Serial.print("\n");
//delay(1000); //wait for 1 second
}

void led(){
  Serial.println( Firebase.getString("Authority"));
  Authority= Firebase.getString("Authority");
  Serial.println(Authority);
  Authority.remove(0, 2);
  Authority.remove(5, 7);
  Serial.println(Authority);
  delay(1000);
  
  if(Authority=="action_taken"){
    digitalWrite(ledpin, HIGH);
    Serial.println("led on");
  }


  
}

void gas(){
 float gassensorAnalog = analogRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);

  Firebase.setFloat("gas",gassensorAnalog);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void loop(){
//test_case();
//delay(2000);
//gas();
//delay(2000);
//temp();
//delay(2000);
//metal();
//delay(2000);
//adxl();
//delay(2000);
//heart();
//delay(2000);
//led();
//delay(2000);
//location();
//delay(2000);
//
//int x = analogRead(xpin);
//delay(1);
//if(x>1700 && x<1800)  //movement
//  {
//   Serial.println("soldier moving");
//   delay(2000);
//    Firebase.setString("MSG1", "soldier moving");
//    Firebase.remove("MSG3");
//    Firebase.remove("MSG2");
//  }
//
//  else if(x>2100 && x<2200)// down
//  {
//    Serial.println("soldier fallen");
//    delay(2000);
//    Firebase.setString("MSG2", "soilder fallen");
//    Firebase.remove("MSG1");
//    Firebase.remove("MSG3");
//  }
//
//  else // straight
//  {
//  Serial.println("all okay");
//  delay(2000);
//  Firebase.setString("MSG3", "all okay");
//  Firebase.remove("MSG1");
//  Firebase.remove("MSG2");
//  }
  
}
