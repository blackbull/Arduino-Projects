
void Read_GPS_Port() {  // читаем данные с GPS и рассшифровываем сразу


  GPSReadTimer.setInterval(GPSReadTime); // запуск в режиме таймаута
  // DEBUG_ln_3(F(" Read_GPS_Port Start "));

  while (Serial.available() && !GPSReadTimer.isReady()) { //пока не истечет таймер, читаем данные с GPS
    gps.encode(Serial.read());
  }


  // DEBUG_ln_3(F(" Read_GPS_Port Stop "));
}

void CheckAndSaveGPS() {
  if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid() && gps.speed.isValid() && gps.hdop.isValid() ) { // проверка на FIX и отсутствие нулей в координатах
    if ((gps.location.lat() != 1) && (gps.location.lng() != 1) && (gps.location.lat() != 0) && (gps.location.lng() != 0) && (gps.hdop.hdop() < 60))
    {

      Fresh_LAT = gps.location.lat();
      Fresh_LNG = gps.location.lng();
      Fresh_date = gps.date;
      Fresh_time = gps.time;
      Fresh_Speed = gps.speed.kmph();
      Fresh_HDOP = gps.hdop.hdop();
      GPSFreshTimer.setTimeout(OldGPSDataTime); //сбрасываем отсчет таймера устаревания данных GPS
      FreshGPSData = true;

      int Distance = 100; //если скорость больше Х км/ч то дистанцию сохранения надо увеличить
      if (gps.speed.kmph() > 110) Distance = 1000;
      else if (gps.speed.kmph() > 80) Distance = 800;
      else if (gps.speed.kmph() > 50) Distance = 600;
      else if (gps.speed.kmph() > 5) Distance = 400;

      if ((float)TinyGPSPlus::distanceBetween(Fresh_LAT, Fresh_LNG, last_Add_LAT, last_Add_LNG) > Distance) //если растояние сместилось более X м - пишем в лог
      {
        saveGPS_to_EEprom();
        last_Add_LAT = Fresh_LAT;
        last_Add_LNG = Fresh_LNG;
      }
    }
  }
}

// функция сохарение данных в EEPROM
void saveGPS_to_EEprom() {

  GPSData.LAT = gps.location.lat();
  GPSData.LNG = gps.location.lng() ;

  GPSData.Speed = gps.speed.kmph();

  GPSData.Month = gps.date.month();
  GPSData.Day = gps.date.day();

  GPSData.Hour = gps.time.hour();
  GPSData.Min = gps.time.minute();
  GPSData.Sec = gps.time.second();

  GPSData.StatusCode = 0;

  WriteGPSData(GPSData);

#ifdef DEBUG_1_ENABLE
  String Temp = GPS_Data_ToString(GPSData);
  DEBUG_1(F(" DataSaved: ")); DEBUG_ln_1(Temp);
#endif
}
