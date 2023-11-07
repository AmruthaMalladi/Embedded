
//relay
const int relay = 26;

//temp lm35
const int analogIn = A6;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

//gas
int Gas_analog = 4;

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,17);

//ultra
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

void setup() {
  
  Serial.begin(115200);
  gsm.begin(9600);
  pinMode(relay, OUTPUT);

  #include <SoftwareSerial.h> 
  SoftwareSerial gsm(16,17);
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  relay_test();
  delay(3000);
  temp();
  delay(1000);
  gas();
  delay(1000);
  SendMessage();
  delay(1000);
  ultra();
  delay(2000);
}

void relay_test() {
  digitalWrite(relay, HIGH);
  Serial.println("current on");
  delay(3000);   
  digitalWrite(relay, LOW);
  Serial.println("current off");
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
}
void gas(){
 int gassensorAnalog = analogRead(Gas_analog);
 Serial.println("gasssensor");
 Serial.println(gassensorAnalog);
 delay(2000);
}

void SendMessage(){
 gsm.println("AT+CMGF=1"); 
 delay(1000);  
 gsm.println("AT+CMGS=\"+917975528296\"\r"); 
 delay(1000);
 gsm.print("hi");
 gsm.println((char)26);
}

void ultra(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
}

void loop(){
   
}
