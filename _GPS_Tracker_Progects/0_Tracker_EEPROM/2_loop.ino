void loop()
{
  Read_GPS_Port(); // читаем данные с GPS пока больше нечего обрабатывать

  if (GPSFreshTimer.isReady()) {
    FreshGPSData = false;  //сбрасываем флаг свежести GPS данных
    DEBUG_ln_2(F("FreshGPSData = false"));
  }
#ifdef DEBUG_2_ENABLE
  //зажигаем светодиод, что свежие GPS данные получены
  digitalWrite(13, FreshGPSData);
#endif


  CheckAndSaveGPS();  // проверяем считанные данные GPS и сохраняем при необходимости
  DEBUG_ln_3(F(" ---------------------------LOOP--------------------- "));
  delay(1000);
}
