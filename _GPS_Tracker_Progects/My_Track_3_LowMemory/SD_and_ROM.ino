// функция сохарение данных на карту памяти
void saveSD_saveEEprom() {
  if (SD_Enabled)
  {
    TinyGPSDate d = gps.date;
    TinyGPSTime t = gps.time;

    char fileName[32];
    sprintf(fileName, "%02d%02d%02d%s", d.year(), d.month(), d.day(), ".csv");
    File dataFile = SD.open(fileName, FILE_WRITE);

    //File dataFile = SD.open("dataGPS.csv", FILE_WRITE);
    // если файл существует и открылся
    if (dataFile) {

      dataFile.print(gps.location.lat(), 4);
      dataFile.print(", ");
      dataFile.print(gps.location.lng(), 4);
      dataFile.print(", ");
      dataFile.print(gps.speed.kmph()); //пишем скорость в описание
      dataFile.print("kmph ");

      char sd[32];
      sprintf(sd, "%02d/%02d/%02d", d.day(), d.month(), d.year());
      dataFile.print(sd);
      dataFile.print(", ");
      char sz[32];
      sprintf(sz, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
      dataFile.println(sz);

      dataFile.close();

      Serial.println("Save OK");
    }
    else Serial.println("Error opening test.csv");
  }

  //сохраняем в EEprom последние точные координаты TODO

}
