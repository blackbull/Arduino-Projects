void setup()
{
  Serial.begin(9600);
  GPS_Port.begin(9600); // скорость обмена с GPS часто именно 9600, но встречается и 4800

  if (SD.begin(4)) SD_Enabled = true; //пытаемся инициализировать sd карту



  //последняя точная координата из памяти (TODO:)
  //dist_LAT = EEPROM.readDouble(0); // читаем из памяти широту нулевой точки
  //dist_LNG = EEPROM.readDouble(4); // читаем из памяти долготу нулевой точки
  //Serial.print("EEPROM POINT, lat: "); Serial.print(dist_LAT, 6); Serial.print(" lng: "); Serial.println(dist_LNG, 6);

}
