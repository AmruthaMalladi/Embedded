

//dc
const int motor1Pin1 = 27; 
const int motor1Pin2 = 26;
const int motor2Pin1 = 25; 
const int motor2Pin2 = 33;
const int enable1Pin = 14; 
const int enable2Pin = 12;
int value1=5, value=10;
 
//ultra
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;

//ir
const int irsensor=4;
const int LED=2;
int stat=0; 

//alcohol sensor
#define MQ3pin 13 //connect the ADC 13 pin t
float sensorValue;//connect the ADC 13 pin t

//relay
int relay = 21;

//gas
int Gas_analog = 39;

//temp
const int analogIn = A6;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;
 
void setup() { 

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(irsensor, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(19, OUTPUT);
  pinMode(3, INPUT);
  
 
  Serial.begin(115200);
 
  // testing
  Serial.print("Testing DC Motor...");

  

  forward();
  delay(3000);
  stop();
  delay(3000);
  backward();
  delay(3000);
  stop();
  delay(3000);
  left();
  delay(3000);
   stop();
  delay(3000);
  right();
  delay(1500);
   stop();
  delay(1500);
  ir();
  delay(2000);
  ultra();
  delay(3000);
  gas();
  delay(1500);
  temp();
  delay(1000);
  alcl();
  delay(2000);
  pump();
  delay(2000);
}
  
  
 


 void forward(){
  digitalWrite(enable1Pin, HIGH); 
  digitalWrite(enable2Pin, HIGH);

  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
   digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  delay(2000);
   digitalWrite(enable1Pin, LOW);
   
   digitalWrite(enable2Pin, LOW);
 }
 void stop(){
   Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  
  delay(1000);
 }
 void backward(){
  
  digitalWrite(enable1Pin, HIGH);
  
   digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
 
  delay(2000);
   digitalWrite(enable1Pin, LOW);
   
   digitalWrite(enable2Pin, LOW);
  
 }
  void left(){
  
  digitalWrite(enable1Pin, HIGH);
  
   digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving left");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
 
  delay(2000);
   digitalWrite(enable1Pin, LOW);
   
   digitalWrite(enable2Pin, LOW);
  
 }
  void right(){
  
  digitalWrite(enable1Pin, HIGH);
  
   digitalWrite(enable2Pin, HIGH);
  Serial.println("Moving right");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
 
  delay(2000);
   digitalWrite(enable1Pin, LOW);
   
   digitalWrite(enable2Pin, LOW);
  
 }

 void ir(){
  stat= digitalRead(irsensor);
  if (stat==HIGH)
  {digitalWrite(LED, HIGH);
  Serial.println("irsensor is high");
 }
 else
 {
  
  digitalWrite(LED, LOW);
  Serial.println("irsensor is low");
 }}
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
  delay(2000);
 }
 void gas(){
   int gassensorAnalog = analogRead(Gas_analog);
   Serial.print("Gas Sensor: ");
   Serial.print(gassensorAnalog);
 
  
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
delay(500);
}
 void alcl(){
  Serial.println("MQ3 warming up!");
  delay(2000);
  sensorValue = analogRead(MQ3pin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
}
void pump()
{
  digitalWrite(relay, HIGH);
  Serial.print("Relay is high: ");
  delay(2000);
  digitalWrite(relay, LOW);
  Serial.print("Relay is high: ");
  delay(2000);
}
void loop() {

 
if( value1==0)
 {
    forward();
    delay(2000);
   
  }
  if( value1==1)
 {
     stop();
    delay(1000);
  }
  if(value1==2)
  {
    backward();
    delay(2000);
  } }
