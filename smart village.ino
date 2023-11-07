
const int irSensor=14;
const int LED=2;
int stat = 0;
const int trigPin = 16;
const int echoPin = 17;
long duration;
int distance;
const int relay = 26;
int TDS_analog = 27; // tds gpio27
int ldrsensorValue;

void setup()
{                
  pinMode(LED, OUTPUT);  
  pinMode(irSensor,INPUT);    
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  ir();
  delay(2000);
  ultra();
  delay(2000);
  waterpump();
  delay(2000);
  tds();
  delay(2000);
  ldr();
  delay(1000);
}

void ir()
{
  stat = digitalRead(irSensor);
 
  if(stat == HIGH)     //Check the sensor output
  {
    digitalWrite(LED, HIGH);   // set the LED on
    Serial.println("irSensorhigh");
  }
  else
  {
    digitalWrite(LED, LOW);    // set the LED off
    Serial.println("irsensorlow");
  }

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
}

void waterpump() {
  
  digitalWrite(relay, LOW);
  Serial.println("water pumping");
  delay(2000); 
  digitalWrite(relay, HIGH);
  Serial.println("water not pumping");
} 
void tds() {
  float sensorValue = analogRead(TDS_analog);
   Serial.println("tds sensorValue");
  Serial.println(sensorValue);
  delay(2000);
} 
void ldr()
{
  ldrsensorValue = analogRead(A6); 
  Serial.print(ldrsensorValue, DEC); 
  Serial.print(" \n"); 
}

void loop (){
}
