const int relay = 26;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
}

void loop() {
  
  digitalWrite(relay, HIGH);
  Serial.println("Current flowing");
  delay(5000); 
  
  digitalWrite(relay, LOW);
  Serial.println("current not flowing");
  delay(5000);
} 
