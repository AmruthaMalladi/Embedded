//firebase
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <Wire.h>
//change
#define FIREBASE_HOST "handtalk-a0dde-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "g9dr0dwA5q6sLVHECO5KvoxxzA1GBIcqYOds3hM6"
#define WIFI_SSID "RSES"
#define WIFI_PASSWORD "46yur1fvfa"

//commands
int voice1 = 27;
int voice2 = 26;
int voice3 = 25;
int voice4 = 12;
int voice5 = 13;


//adxl
const int xpin = 33;
const int ypin = 34;
const int zpin = 35;

//lm35
const int analogIn = 32 ;
int RawValue = 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

//buzzer
int Buzzer = 4;

//PANIC
const int PushButton = 18;

//gps
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(4, 1);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;      
volatile float minutes, seconds;
volatile int degree, secs, mins;




void setup()
{
  Serial.begin(115200);

  //commands
  pinMode (voice1, OUTPUT);
  pinMode (voice2, OUTPUT);
  pinMode (voice3, OUTPUT);
  pinMode (voice4, OUTPUT);
  pinMode (voice5, OUTPUT);

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
  lcd.backlight(
    );

  //buzz
  pinMode (Buzzer, OUTPUT);
  //PANIC
  pinMode(PushButton, INPUT);


}



void temp() {
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 2048.0) * 3300;
  tempC = Voltage * 0.1;
  tempF = (tempC * 1.8) + 32;
  Serial.print("Raw Value = " );
  Serial.print(RawValue);
  Serial.print("\t milli volts = ");
  Serial.print(Voltage, 0); //
  Serial.print("\t Temperature in C = ");
  Serial.print(tempC, 1);
  Serial.print("\t Temperature in F = ");
  Serial.println(tempF, 1);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempinC");
  lcd.print(tempC);
  lcd.setCursor(0, 1);
  lcd.print("Temp in F");
  lcd.print(tempF);
  delay(2000);

  Firebase.setFloat("temperature", tempC);
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);
    Firebase.setString("Location","12.7837° N, 77.4965° E");
}
void buzz_on() {
  digitalWrite (Buzzer, HIGH); //turn buzzer on
}

void buzz_off() {
  digitalWrite (Buzzer, LOW);  //turn buzzer off
}

void panic() {
  int Push_button_state = digitalRead(PushButton);
  if ( Push_button_state == HIGH )
  {
    buzz_on();
    digitalWrite(Buzzer, HIGH);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I NEED HELP");
    delay(2000);
    Firebase.setString("alert", "danger");

  }
  else
  {
    buzz_off();
    digitalWrite(Buzzer, LOW);
    Firebase.remove("alert");
  }
}

void loc() {
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
          Serial.println("12.7837 N");
          Serial.print("Longitude : ");
          Serial.println("77.4965 E");
        }
        else
        {
          
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(lat_val, 6);
          Serial.print("Latitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
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
          Serial.print("is the location");
        }
        else
        {
          char time_string[32];
          Serial.print(time_string);    
        }
}

void gesture() {

  int x = analogRead(xpin);
  delay(1);
  int y = analogRead(ypin);
  delay(1);
  int z = analogRead(zpin);

  float zero_G = 512.0;
  float scale = 102.3;
  Serial.println("x axis");
  Serial.print(((float)x - 331.5) / 65 * 9.8);
  Serial.print("\t");
  Serial.println("y axis");
  Serial.print(((float)y - 329.5) / 68.5 * 9.8);
  Serial.print("\t");
  Serial.println("z axis");
  Serial.print(((float)z - 340) / 68 * 9.8);
  Serial.print("\n");


}

void loop() {
  temp();
  delay(2000);
  panic();
  delay(2000);
  gesture();
  delay(1000);

  int x = analogRead(xpin);
  x = ((float)x - 331.5) / 65 * 9.8;

  if (x > 1700 && x < 1800) //strigt
  {
    Serial.println("I NEED HELP");
    delay(2000);
    digitalWrite (voice1, LOW);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I NEED HELP");
    delay(2000);
    Firebase.setString("MSG", "I_NEED_HELP");
    delay(2000);

  }

  else if (x > 1800 && x < 1900) //opposite
  {
    Serial.println("I'M HUNGRY");
    Serial.println("I'M HUNGRY");
    delay(2000);
    digitalWrite (voice2, LOW);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I'M HUNGRY");

    Firebase.setString("MSG", "I'M_HUNGRY");
    delay(2000);
  }

  else if (x > 2100 && x < 2200) // down
  {
    Serial.println("I NEED TO GO OUT");
    Serial.println("I NEED TO GO OUT");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I NEED TO GO OUT");
    delay(2000);
    digitalWrite (voice3, LOW);
    delay(2000);
    Firebase.setString("MSG", "I_NEED_TO_GO_OUT");
    delay(2000);

  }

  else if (x > 1600 && x < 1700) //right side
  {
    Serial.println("I NEED SOME WATER");
    Serial.println("I NEED SOME WATER");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I NEED WATER");
    delay(2000);
    digitalWrite (voice4, LOW);
    delay(2000);
    Firebase.setString("MSG", "I_NEED_SOME_WATER");
    delay(2000);
  }

  else if (x > 200 && x < 250) //strigh side
  {
    Serial.println("I WANT MILK");
    Firebase.setString("MSG", "I_WANT_MILK");
    delay(2000);
    digitalWrite (voice5, LOW);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I WANT MILK");
    delay(2000);

  }

  else
  {
    Serial.println("all okay");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("all okay");
    delay(2000);
    Firebase.setString("MSG", "ALL_OKAY");
    delay(2000);
  }


}
