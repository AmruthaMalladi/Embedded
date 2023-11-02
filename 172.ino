//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17);

//buzzer
int Buzzer = 4;

//heart
int sensorPin = 34;                              
float sensorValue = 0;                             
int count = 9;
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;

//max
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected()
{
    Serial.println("Beat!");
}


//LM35
const int analogIn = 26;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;


void setup() {
Serial.begin(115200);
  //gsm
  delay(1000);
  gsm.begin(9600);

  //buzzer
   pinMode (Buzzer, OUTPUT);


Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);

max30100();
delay(1000);
buzz();
delay(2000);
heart();
delay(2000);
temp();
delay(2000);
SendMessage();
delay(1000);
}

void buzz(){
  digitalWrite (Buzzer, HIGH); 
  delay(2000);
  digitalWrite (Buzzer, LOW);  
  delay(2000);
  
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
Serial.println (heartrate);                        // Display BPM in the Serial Monitor
Serial.println ();
count = 0;
delay(2000);
}




void temp(){
RawValue = analogRead(analogIn);
Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
tempC = Voltage * 0.1;
tempF = (tempC * 1.8) + 32; // conver to F
Serial.print("Raw Value = " ); // shows pre-scaled value
Serial.print(RawValue);
Serial.print("\t milli volts = "); // shows the voltage measured
Serial.print(Voltage,0); //
Serial.print("\t Temperature in C = ");
Serial.print(tempC,1);
Serial.print("\t Temperature in F = ");
Serial.println(tempF,1);
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
void max30100()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
 
        tsLastReport = millis();
    }
}

void loop(){
  
}

  

  
