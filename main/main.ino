// Určenie knižníc potrebných pre projekt
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// Definovanie pinov použitých na Arduine
#define SS_PIN 10
#define RST_PIN 9

// Definovanie rozlíšenia LCD displeju
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definovanie premenných využívaných pri skladovaní a zobrazovaní prebraných dát
byte readCard[4];
String tagID = "";
String simonID = "4285682";
String tobiasID = "4285582";
String meno = "";
String vyroba = "";
String datum = "";
String cas = "";
String osobneCislo = "";

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{
  // Spustenie Arduina a LCD displeja, vrátane tzv. backlightu
  Serial.begin(9600);
  SPI.begin();
  lcd.init();
  lcd.backlight();

  mfrc522.PCD_Init();
  delay(4);

  mfrc522.PCD_DumpVersionToSerial();
  //Zobrazenie úvodnej požiadavky
  lcd.setCursor(0, 0);
  lcd.print("Naskenuj kartu");
  Serial.println("Naskenuj kartu>>");
}

boolean getID() 
{
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}

void loop() 
{
  // Spracovanie dát čítačky
  while (getID()) {
    if (tagID == tobiasID) {
      lcd.clear();
      lcd.setCursor(0, 0);
      meno = "Tobias Buran";
      vyroba = "FER";
      osobneCislo = "SC69223";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(meno);
      lcd.setCursor(0, 1);
      lcd.print(vyroba + " / " + osobneCislo);
      } else if (tagID == simonID) {
      meno = "Simon Gomola";
      vyroba = "PEI";
      osobneCislo = "SC69171";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(meno);
      lcd.setCursor(0, 1);
      lcd.print(vyroba + " / " + osobneCislo);
      }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    else {
      Serial.print(tagID);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Neznama karta");
      Serial.println(" Access Denied!");
      Serial.println("--------------------------");
    }
  }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Naskenuj kartu");
    Serial.println(" Access Control ");
    Serial.println("Scan Your Card>>");
  }

