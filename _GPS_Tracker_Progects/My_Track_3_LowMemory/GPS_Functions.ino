static void Read_GPS_Port(unsigned long ms) {  // читаем данные с GPS и рассшифровываем сразу
  unsigned long start = millis();
  do {
    while (GPS_Port.available()) {
      gps.encode(GPS_Port.read());
      Serial.print(',');
    }
  } while (millis() - start < ms);
}
