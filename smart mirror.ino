//relay
const int relay1 = 26;
const int relay2 = 27;
const int relay3 = 28;
const int relay4 = 29;

//ir
const int irSensor=18;
const int LED=2;
int stat = 0;

//ldr
int ldrValue;

//adxl
const int xpin = 33; 
const int ypin = 34; 
const int zpin = 35;
 
//pir
int ledPin = 13;                
int inputPin = 2;               
int pirState = LOW;             
int val = 0; 

void setup() {
Serial.begin(115200);

//relay
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);

//ir
pinMode(LED, OUTPUT);         
pinMode(irSensor,INPUT); 

//pir
pinMode(ledPin, OUTPUT);      
pinMode(inputPin, INPUT);

relay1_on();
delay(5000);
relay1_off();
delay(5000);
relay2_on();
delay(5000);
relay1_off();
delay(5000);
relay3_on();
delay(5000);
relay1_off();
delay(5000);
relay4_on();
delay(5000);
relay1_off();
delay(5000);
ir();
delay(2000); 
ldr();
delay(1000);
adxl();
delay(2000);
pir();
delay(2000);
}

void relay1_on() { 
  digitalWrite(relay1, HIGH);
  Serial.println("HIGH");
} 

void relay1_off(){ 
  digitalWrite(relay1, LOW);
  Serial.println("LOW");
} 
void relay2_on() { 
  digitalWrite(relay2, HIGH);
  Serial.println("HIGH");
} 

void relay2_off(){ 
  digitalWrite(relay2, LOW);
  Serial.println("LOW");
} 
void relay3_on() { 
  digitalWrite(relay3, HIGH);
  Serial.println("HIGH");
} 

void relay3_off(){ 
  digitalWrite(relay3, LOW);
  Serial.println("LOW");
} 
void relay4_on() { 
  digitalWrite(relay4, HIGH);
  Serial.println("HIGH");
} 
void relay_4off(){ 
  digitalWrite(relay4, LOW);
  Serial.println("LOW");
}  
void ir()
{
  stat = digitalRead(irSensor);
  if(stat == HIGH)    
  {
    digitalWrite(LED, HIGH);  
    Serial.println("irSensorhigh");
    delay(2000);
  }
  else
  {
    digitalWrite(LED, LOW);    
    Serial.println("irsensorlow");
    delay(2000);
  }
}
void ldr()
{
  ldrValue = analogRead(36); 
  Serial.print(ldrValue, DEC);
  Serial.print(" \n"); 
}
void adxl()
{
int x = analogRead(xpin);
delay(1); //
int y = analogRead(ypin);
delay(1);
int z = analogRead(zpin); 
float zero_G = 512.0; 
float scale = 102.3; 
Serial.print(((float)x - 331.5)/65*9.8); 
Serial.print("\t");
Serial.print(((float)y - 329.5)/68.5*9.8); 
Serial.print("\t");
Serial.print(((float)z - 340)/68*9.8);
Serial.print("\n");
}
void pir(){
  val = digitalRead(inputPin);  
  if (val == HIGH) {           
    digitalWrite(ledPin, HIGH);  
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); 
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void loop(){
  
}
