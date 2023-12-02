
#include <Arduino.h>
#include <EEPROM.h>
#include <CRC16.h>

#define BAUD_RATE 2400
#define TEXT_SIZE 1000

uint8_t text_data[TEXT_SIZE];
uint16_t text_index = 0;

void storeDataToEEPROM(uint8_t data) {
  if (text_index < TEXT_SIZE) {
    EEPROM.update(text_index, data);
    text_index++;
  } else {
    // EEPROM is full, handle this case as needed
    // For example, you could print an error message or take appropriate action
    Serial.println("EEPROM is full!");
  }
}

uint16_t calculateCRC16() {
  CRC16 crc;
  for (uint16_t i = 0; i < TEXT_SIZE; i++) {
    crc.update(EEPROM.read(i));
  }
  return crc.finalize();
}

void sendDataToPC() {
  // Retrieve data from EEPROM and send to PC
  for (uint16_t i = 0; i < TEXT_SIZE; i++) {
    Serial.write(EEPROM.read(i));
  }

  // Calculate and send CRC checksum
  uint16_t crc_result = calculateCRC16();
  Serial.write(crc_result & 0xFF);
  Serial.write((crc_result >> 8) & 0xFF);

  // Loop forever
  while (true);
}

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  // Wait for data to be received
  while (!Serial.available());

  uint8_t received_data = Serial.read();

  // Store data in EEPROM
  storeDataToEEPROM(received_data);

  // Check for end of transmission
  if (text_index == TEXT_SIZE) {
    sendDataToPC();
  }
}
