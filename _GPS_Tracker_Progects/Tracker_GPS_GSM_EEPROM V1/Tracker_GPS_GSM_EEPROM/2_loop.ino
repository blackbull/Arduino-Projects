void loop()
{
#ifdef DEBUG_2_ENABLE
  butt1.tick();
  if (butt1.isPress()) {
    FreshGPSData = false;
    /*
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 0));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 4));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 8));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 12));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 16));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 20));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 24));
        DEBUG_ln_2(Get_Last_GPS_Data_String(4, 28));
    */

    //DoSMS_Command ("last0800", "+79527801280");
    //DoSMS_Command ("last0808", "+79527801280");
    // DoSMS_Command ("lastal00", "+79527801280");
    //DoSMS_Command ("where", "+79527801280");
    //DoSMS_Command ("getopt", "+79527801280");
  }
#endif

  //---------------------обработка GPS----------------------

  Read_GPS_Port(); // читаем данные с GPS пока больше нечего обрабатывать
  if (GPSFreshTimer.isReady()) {
    FreshGPSData = false;  //сбрасываем флаг свежести GPS данных
    DEBUG_ln_2(F("FreshGPSData = false"));
  }


#ifdef DEBUG_1_ENABLE
  //зажигаем светодиод, что свежие GPS данные получены
  digitalWrite(13, FreshGPSData);
#endif

  CheckAndSaveGPS();  // проверяем считанные данные GPS и сохраняем при необходимости


  //-------------------обработка GSM------------------------

  if (InitialGSMFlag) {
    CheckGSM_RING();
    CheckAndParsingSMS();
    CheckGSM_RING();

    Check_Wait_ToSend_NewGPS_position(); //проверяем, нужна ли отправка свежих координат по смс
    Check_Wait_ToSend_History_GPS_position();  //проверяем, нужна ли отправка истории координат по смс
  }
  else InitialGSM();

  /*
    #ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
    if (Serial.available())  {                          // Ожидаем команды по Serial...
      SIM800.write(Serial.read());                      // ...и отправляем полученную команду модему
    };
    #endif
  */


  //DEBUG_ln_2(F("------------------------------loop end-------------------------------"));
}
