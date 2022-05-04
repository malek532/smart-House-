#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

int pos = 0;

Servo servo_9;
#define SS_PIN 10  // link SS_PIN port 10
#define RST_PIN 9  // link RST_PIN port 9
MFRC522 mfrc522(SS_PIN, RST_PIN); //create MFRC522 instance
void setup() {
  servo_9.attach(6);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();//Iniate mfrc522
  Serial.println("Put your card to the reader...");
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly
  if (!mfrc522.PICC_IsNewCardPresent())//Check if there is a new card
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())//Check if there is a card
  {
    return;
  }
  //Show UID on Serial
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  { Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B3 35 5B 11")//substring chaine
  {
    for (pos = 90; pos >= 0; pos--) {
      servo_9.write(pos);
      delay(15);
    };
    delay(3000);
    for (pos = 0; pos <= 90; pos++) {
      servo_9.write(pos);
      delay(15);
    };
    delay(500);
    Serial.println("Authorized access");
    Serial.println();
    delay(400);
  }
  else
  {
    Serial.println("Access denied");
  }

}
