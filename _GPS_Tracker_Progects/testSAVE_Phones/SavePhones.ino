void SavePhones() {
  char ch[39];
  Phones.toCharArray(ch, 39);
 DEBUG_3("save: "); DEBUG_ln_3(ch);
  
  EEPROM.put(PhonesAdress, ch);
}

void LoadPhones() {
  char message[39];
  EEPROM.get(PhonesAdress, message);
  DEBUG_ln_3(message);
  DEBUG_ln_3(String(message));  
  Phones =  String(message);
  DEBUG_ln_3(Phones);
}
