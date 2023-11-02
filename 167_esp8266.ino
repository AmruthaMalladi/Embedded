//switch,lcd,buzzer, gsm, rfid

//gsm
#include <SoftwareSerial.h> 
SoftwareSerial gsm(16,0);

//switch
const int switch_pin=15;
bool switch_state;

//buzzer
int Buzzer = 12;


//rfid
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 


void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  
  //rfid
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

 //buzz
 pinMode (Buzzer, OUTPUT);

 //switch
 pinMode(switch_pin, INPUT);

  //GSM
  delay(1000);
  gsm.begin(9600);

  rfid();
  delay(3000);
  SendMessage();
  delay(1000);
  buzz_on();
  delay(1000);
  buzz_off();
  delay(1000);
  swi();
  delay(1000);

}

void SendMessage()
{
  gsm.println("AT+CMGF=1"); 
  delay(1000);  
  gsm.println("AT+CMGS=\"+917975528296\"\r"); 
  delay(1000);
//  gsm.println(e);
// delay(100);
 gsm.print("hi");
 gsm.println((char)26);
  delay(1000);
}

void rfid() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
  }
}

void buzz_on(){
  digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);
}

void buzz_off(){
  digitalWrite (Buzzer, LOW);  //turn buzzer off
  delay(1000);
}

void swi(){
  switch_state= digitalRead(switch_pin);
  Serial.println("switch");
  Serial.println(switch_state);
}

void loop() {

}
