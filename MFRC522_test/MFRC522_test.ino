/*
 * MFRC522 RFID reader test (adapted from MFRC522 DumpInfo example)
 * Library: MFRC522 by GithubCommunity
 *
 * Typical pin layout used (Arduino Uno R3):
 * -------------------------------------
 * MFRC522      Arduino
 * Pin          Pin
 * -------------------------------------
 * RST          9
 * SDA(SS)      10
 * MOSI         11
 * MISO         12
 * SCK          13
 * 3.3V         3.3V  (DO NOT connect to 5V!)
 * GND          GND
 * IRQ          unconnected
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522
  delay(4);            // Optional delay. Some board do need more time after init to be ready

  // Check version register to make sure SPI wiring works
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Firmware Version: 0x"));
  Serial.println(v, HEX);
  if (v == 0x00 || v == 0xFF) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected? (Check 3.3V and SPI pins)"));
    while (1);
  }

  Serial.println(F("Scan PICC to see UID and type..."));
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10)
      Serial.print(F(" 0"));
    else
      Serial.print(F(" "));
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Dump PICC type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print(F("PICC type: "));
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  Serial.println();

  // Halt PICC so it doesn't keep reading the same card in a loop
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
