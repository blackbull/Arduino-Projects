void setup()
{
  GPS_Port.begin(9600); // скорость обмена с GPS часто именно 9600, но встречается и 4800

#ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
  Serial.begin(9600);
#endif
  DEBUG_ln_1(F("======================================================================"));

#ifdef DEBUG_2_ENABLE
  //зажигаем светодиод, что GPS получен
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);  
#endif

#ifdef FistInitial
  DEBUG_2(F("OptionsStruct size ")); DEBUG_ln_2(sizeof(OptionsStruct));
  DEBUG_2(F("LastWritingStruct size ")); DEBUG_ln_2(sizeof(LastWritingStruct));
  DEBUG_2(F("GpsDataStruct size ")); DEBUG_ln_2(sizeof(GpsDataStruct));
  DEBUG_ln_2(F("-----------------------------------------"));

  InitializingOptions();
  LoadFullOptions();

  while (1) delay(1000000);
#endif

  LoadOptions(); //загрузить опции из ROM

#ifdef TestFunctions
  Test_WR_Data();
#endif

#ifdef DEBUG_1_ENABLE
  PrintFull_Options();//выводим в консоль все опции
  PrintlnFull_GPS_Data(); //выводим все данные GPS
#endif

  //загружаем последние данные в переменные для сравнения новых
  last_Add_LAT = GPSData.LAT;
  last_Add_LNG = GPSData.LNG;
}
