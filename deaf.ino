#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

// Set these to run example.
#define FIREBASE_HOST "sample-9e85e.firebaseio.com"
#define FIREBASE_AUTH "P6uw4XlNwgdEWMdBqi7kHhOhv9XGj9H3glnQJ3sx"
#define WIFI_SSID "JioFi3_833467"
#define WIFI_PASSWORD "46yur1fvfa"

#define RXD2 16
#define TXD2 17

int sw=19;
 
 
void setup()
{
  // Initialize serial communication at 115200 baud
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(115200);
  delay(10);
  Serial.print("#################\nInitializing...");
  pinMode(sw, INPUT);


  gsmtest();
}
void loop()
{
 //  Get raw accelerometer data for each axis
  int rawX = analogRead(36);
  int rawY = analogRead(39);
  int rawZ = analogRead(34);
 
  Serial.print("X: "); Serial.println(rawX);
  Serial.print("Y: "); Serial.println(rawY);
  Serial.print("Z: "); Serial.println(rawZ);
  delay(2000);
  delay(1000);


int swvalue=digitalRead(sw);
 Serial.print("sw value: "); Serial.println(swvalue);
  if(swvalue==1)
  {
    gsmsms();
    Serial.print("sms sent");
  }

  if(rawX>1700 && rawX<1800)  //strigt
  {
    Serial.println("I NEED HELP");
    Firebase.setString("MSG", "I_NEED_HELP");
    //Firebase.remove("MSG");
    Firebase.remove("MSG1");
    Firebase.remove("MSG2");
    Firebase.remove("MSG3");
    Firebase.remove("MSG4");
 
  }

  else if(rawX>1800 && rawX<1900)  //opposite
  {
    Serial.println("I'M HUNGRY");
    Firebase.setString("MSG1", "I'M_HUNGRY");
    Firebase.remove("MSG");
    //Firebase.remove("MSG1");
    Firebase.remove("MSG2");
    Firebase.remove("MSG3");
    Firebase.remove("MSG4");
  }

  else if(rawX>2100 && rawX<2200)// down
  {
    Serial.println("I NEED TO GO OUT");
    Firebase.setString("MSG2", "I_NEED_TO_GO_OUT");
    Firebase.remove("MSG");
    Firebase.remove("MSG1");
    //Firebase.remove("MSG2");
    Firebase.remove("MSG3");
    Firebase.remove("MSG4");
  }

    else if(rawX>1600 && rawX<1700)//right side
  {
    Serial.println("I NEED SOME WATER");
    Firebase.setString("MSG3", "I_NEED_SOME_WATER");
    Firebase.remove("MSG");
    Firebase.remove("MSG1");
    Firebase.remove("MSG2");
    //Firebase.remove("MSG3");
    Firebase.remove("MSG4");
  }

    else if(rawX>1400 && rawX<1500)//strigh side
  {
    Serial.println("I WANT MILK");
    Firebase.setString("MSG4", "I_WANT_MILK");
    Firebase.remove("MSG");
    Firebase.remove("MSG1");
    Firebase.remove("MSG2");
    Firebase.remove("MSG3");
    //Firebase.remove("MSG4");
  }

  else
  {
    Serial.println("BE HAPPY");
    Firebase.remove("MSG");
    Firebase.remove("MSG1");
    Firebase.remove("MSG2");
    Firebase.remove("MSG3");
    Firebase.remove("MSG4");
  }

 
}

void gsmtest()
{

  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+919980878361\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println("This is test SMS from ESP32");// The SMS text you want to send
  Serial.println("sms sent");
  delay(4000);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void gsmsms()
{

  Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial2.println("AT+CMGS=\"+919980878361\"\r"); // Replace x with mobile number
  delay(1000);
  Serial2.println("Emergency Help me!");// The SMS text you want to send
  Serial.println("sms sent");
  delay(4000);
  Serial2.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
