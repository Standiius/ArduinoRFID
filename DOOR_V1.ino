/*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>

#include <Servo.h>

Servo doorservo;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int rood = 9;
int groen = 7;
int geel = 4;
const int buzzer = 5;

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  doorservo.attach(8);
  doorservo.write(0);
  pinMode(rood, OUTPUT);
  pinMode(groen, OUTPUT);
  pinMode(geel, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(rood, HIGH);
  digitalWrite(groen, LOW);
  digitalWrite(geel, LOW);

}
void loop() 
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
  if (content.substring(1) == "3B EE 4D 1B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    doorservo.write(90);
    digitalWrite(groen, HIGH);
    digitalWrite(rood, LOW);
    digitalWrite(geel, HIGH);
    tone(buzzer, 1000, 1000);
    delay(1000);
    tone(buzzer, 1500, 1000);
    delay(4000);
    tone(buzzer, 1000, 1000);
    delay(1000);
    tone(buzzer, 500, 1000);
    delay(1000);
    doorservo.write(0);
    digitalWrite(rood, HIGH);
    digitalWrite(groen, LOW);
    delay(4000);
    digitalWrite(geel, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(3000);
    doorservo.write(0);
  }
} 
