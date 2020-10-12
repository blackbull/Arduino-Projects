void loop()
{
  if (gps.location.isValid() && gps.date.isValid()) { // проверка на FIX и отсутствие нулей в координатах
    if ((gps.location.lat() != 1) or (gps.location.lng() != 1))
    {
      FreshGPSData = true; //данные обновлены
      if ((float)TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), last_LAT, last_LNG) > 50) //если растояние сместилось более 50 м - пишем в лог
      {
        saveSD_saveEEprom();
        last_LAT = gps.location.lat();
        last_LNG = gps.location.lng();
      }

    }
  }

  Read_GPS_Port(100); // читаем данные с GPS пока больше нечего обрабатывать


}
