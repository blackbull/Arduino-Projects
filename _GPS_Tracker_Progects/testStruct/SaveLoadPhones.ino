void SavePhones() {
  //Serial.println(Phones.length());
  char ch[39];
  Phones.toCharArray(ch, 39);
  //Serial.println(sizeof(ch));

  EEPROM.put(PhonesAdress, ch);
}

void LoadPhones() {
  char message[39];
  EEPROM.get(PhonesAdress, message);
  String stringOne =  String(message);
  Serial.println(stringOne);
}
