
void Add_Defaukt_keys() {

  Serial.println("adding universal key to EEPROM ");
  //добавляем универсальные ключи в память

  /*  //тест добавления максимума ключей
      keyID[0] = 0x1; keyID[1] = 0x1; keyID[2] = 0x1; keyID[3] = 0x1; keyID[4] = 0x1; keyID[5] = 0x1; keyID[6] = 0x1; keyID[7] = 0x1;
      for (byte j = 1; j <= maxKeyCount; j++) {
        keyID[0] = j;
        EPPROM_AddKey(keyID);
      }
  */
  keyID[0] = 0x1; keyID[1] = 0xFF; keyID[2] = 0xFF; keyID[3] = 0xFF; keyID[4] = 0xFF; keyID[5] = 0xFF; keyID[6] = 0xFF; keyID[7] = 0x2F;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0xBE; keyID[2] = 0x40; keyID[3] = 0x11; keyID[4] = 0x5A; keyID[5] = 0x36; keyID[6] = 0x0; keyID[7] = 0xE1;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0xBE; keyID[2] = 0x40; keyID[3] = 0x11; keyID[4] = 0x5A; keyID[5] = 0x56; keyID[6] = 0x0; keyID[7] = 0xBB;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0xBE; keyID[2] = 0x40; keyID[3] = 0x11; keyID[4] = 0x0; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0x77;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0xBE; keyID[2] = 0x40; keyID[3] = 0x11; keyID[4] = 0xA; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0x1D;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0xFF; keyID[2] = 0xFF; keyID[3] = 0xFF; keyID[4] = 0xFF; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0x9B;
  EPPROM_AddKey(keyID);
  keyID[0] = 0xFF; keyID[1] = 0xFF; keyID[2] = 0xFF; keyID[3] = 0xFF; keyID[4] = 0xFF; keyID[5] = 0xFF; keyID[6] = 0xFF; keyID[7] = 0x14;
  EPPROM_AddKey(keyID);
  keyID[0] = 0xFF; keyID[1] = 0x8E; keyID[2] = 0x80; keyID[3] = 0x2; keyID[4] = 0x8B; keyID[5] = 0x29; keyID[6] = 0x5F; keyID[7] = 0xD0;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1; keyID[1] = 0x96; keyID[2] = 0x5D; keyID[3] = 0x28; keyID[4] = 0x9; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0xA5;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x2B; keyID[1] = 0x1E; keyID[2] = 0xB8; keyID[3] = 0x76; keyID[4] = 0x0; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0xC1;
  EPPROM_AddKey(keyID);
  keyID[0] = 0x1B; keyID[1] = 0xBD; keyID[2] = 0xBD; keyID[3] = 0x7D; keyID[4] = 0xD0; keyID[5] = 0x0; keyID[6] = 0x0; keyID[7] = 0x0;
  EPPROM_AddKey(keyID);



  /* //тест каких то еще ключей
    keyID[0] = 0xFF; keyID[1] = 0xb0; keyID[2] = 0x60; keyID[3] = 0x01; keyID[4] = 0xba; keyID[5] = 0xc2; keyID[6] = 0xe0; keyID[7] = 0xa0;
    CheckCRC(keyID);
    EPPROM_AddKey(keyID);

    keyID[0] = 0xFF; keyID[1] = 0xb0; keyID[2] = 0x60; keyID[3] = 0x01; keyID[4] = 0xba; keyID[5] = 0xc2; keyID[6] = 0xe0; keyID[7] = 0xa0;
    EPPROM_AddKey(keyID);

    keyID[0] = 0x01; keyID[1] = 0x00; keyID[2] = 0x00; keyID[3] = 0xff; keyID[4] = 0xff; keyID[5] = 0xff; keyID[6] = 0xff; keyID[7] = 0x9b;
    CheckCRC(keyID);
    EPPROM_AddKey(keyID);

    keyID[0] = 0x01; keyID[1] = 0x00; keyID[2] = 0x00; keyID[3] = 0x00; keyID[4] = 0x00; keyID[5] = 0x00; keyID[6] = 0x00; keyID[7] = 0x01;
    CheckCRC(keyID);
    EPPROM_AddKey(keyID);
  */




  myOLED.print("adding universal key to EEPROM", 0, 12);
  myOLED.update();
}


void WriteKeyToSerial(byte buf[]) {
  for (byte i = 0; i < 8; i++) {
    Serial.print(buf[i], HEX); Serial.print(F(":"));
  }
}
void WriteKeyToSerial_CodeFormat(byte buf[]) {
  for (byte i = 0; i < 8; i++) {
    Serial.print(F("keyID[")); Serial.print(i); Serial.print(F("] = 0x"));
    Serial.print(buf[i], HEX); Serial.print(F("; "));
  }
}

void WriteAllKeyfromEEPROM() {
  byte buf1[8];
  Serial.println("Read ALL key code from EEPROM: ");
  for (byte j = 1; j <= EEPROM_key_count; j++) { // ищем ключ в eeprom.
    EEPROM.get(j * sizeof(buf1), buf1);
    WriteKeyToSerial(buf1);
    Serial.println();
  }
}

void WriteAllKeyfromEEPROM_codeFormat() {
  byte buf1[8];
  Serial.println("Code Format: ");
  for (byte j = 1; j <= EEPROM_key_count; j++) { // ищем ключ в eeprom.
    EEPROM.get(j * sizeof(buf1), buf1);
    WriteKeyToSerial_CodeFormat(buf1);
    Serial.println();
  }
}

//проверка crc
void CheckCRC(byte buf[]) {
  byte CRC = OneWire::crc8(buf, 7);
  if (CRC != buf[7]) {
    buf[7] = CRC;
    Serial.print("CRC is not valid! New CRC ="); Serial.println(buf[7], HEX);
  }
}
