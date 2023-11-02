//#include <WiFi.h>
//#include <IOXhop_FirebaseESP32.h>
#include <HX711.h>  //You must have this library in your arduino library folder
//
//
//#define FIREBASE_HOST "refrigraju-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "INKvEikuflK69Vjlv7Td93Lz1V7mw49dedVfebP4"
//#define WIFI_SSID "Y1"                                           // input your home or public wifi name 
//#define WIFI_PASSWORD "00000000"

#define DOUT  23
#define CLK  22
HX711 scale(DOUT, CLK);
const int light = 26;
const int MQ6pin = 34;
const int trigPin = 12;
const int echoPin = 14;
const int temppin = 32;

int RawValue = 0;
double Voltage = 0;
double tempC = 0;
long duration;
int distance;
int sensorValue1 = 0;
String lightbutton;

void setup() {
  Serial.begin(115200);
   Serial2.begin(9600);
  delay(100);
  Serial.println("Press T to tare");
  scale.set_scale(970);            //Calibration Factor obtained from first sketch
  scale.tare();
 
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(MQ6pin, INPUT);
  pinMode(temppin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
//  Serial.print("Connecting to ");
//  Serial.print(WIFI_SSID);
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }
//  Serial.println();
//  Serial.print("Connected to ");
//  Serial.println(WIFI_SSID);
//  Serial.print("IP Address is : ");
//  Serial.println(WiFi.localIP());                                                      //print local IP address
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
//  delay(500);
  TestMessage();
  delay(500);
  light_on();
}


void TestMessage()
{
  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+919448847874\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println("This is Test MSG, I am SMS from GSM Module");// The SMS text you want to send
  Serial.print("MSG Sent");
  delay(100);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}



void gas_SendMessage()
{
  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+918123162422\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println(" Gas Alert Message");// The SMS text you want to send
  Serial.println("MSG1 Sent");
  delay(100);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void temp_SendMessage()
{
  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+918123162422\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println(" Temperature Alert Message");// The SMS text you want to send
  Serial.println("MSG1 Sent");
  delay(100);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void weight_SendMessage()
{
  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+918123162422\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println(" Weight Alert Message");// The SMS text you want to send
  Serial.println("MSG1 Sent");
  delay(100);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void distance_SendMessage()
{
  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+918123162422\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println(" Distance Alert Message");// The SMS text you want to send
  Serial.println("MSG1 Sent");
  delay(100);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);

}

void temp() {
  RawValue = analogRead(temppin);
  Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
  tempC = Voltage * 0.1;
  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);
  Serial.print("\t milli volts = "); // shows the voltage measured
  Serial.print(Voltage, 0); //
  Serial.print("\t Temperature in C = ");
  Serial.print(tempC, 1);
  //Firebase.setFloat("Temperature", tempC);
  delay(1000);
  if (tempC > 40)
  {
    temp_SendMessage();
  }

}

void MQ6_call() {
  Serial.println("MQ6 warming up!");
  delay(1000);
  sensorValue1 = analogRead(MQ6pin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue1);
  delay(300);
  if (sensorValue1 < 1000)
  {
    Serial.println("MQ6 alert");
    gas_SendMessage();
    delay(500);

  }
//  Firebase.setFloat("MQ6", sensorValue1);
//  delay(1000);
}

void ultra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
//  Firebase.setFloat("Distance", distance);
  delay(1000);
  if (distance < 20)
  {
    distance_SendMessage();
  }
}

void light_on() {
  Serial.println("light on");
  digitalWrite(light, HIGH);
  delay(2000);
  digitalWrite(light, LOW);
  delay(500);

}
void loop() {
  Serial.println("Reading weight.. ");
  delay(2000);
  Serial.print("Weight: ");
  Serial.print(scale.get_units());
  Serial.println(" gm");
  if (scale.get_units() < 20)
  {
    weight_SendMessage();
  }
//  Firebase.setFloat("Weight", scale.get_units());
  delay(1000);
  ultra();
  delay(300);
  MQ6_call();
  delay(300);
  temp();
  delay(300);
 // lightbutton = Firebase.getString("LightStatus");
  delay(100);
  Serial.println(lightbutton);
  if (lightbutton == "1") {
    Serial.println("Light On");
    light_on();
    delay(300);
  }
  if (lightbutton == "0") {
    Serial.println("Light Off");
    delay(300);
  }

}
