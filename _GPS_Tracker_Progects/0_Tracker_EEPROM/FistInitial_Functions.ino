
#ifdef FistInitial
void InitializingOptions() {
  Phones = "111111111111_222222222222_333333333333";
  SavePhones();
  OptionsSTR.SleepMode = 0;
  OptionsSTR.LastWritingOPT_Adres = LastWritingStructAdress;
  OptionsSTR.MaxWriteCount = 1000;

#ifdef TestFunctions
  OptionsSTR.MaxWriteCount = 10; //для теста уменьшием количество записей на ячейку
#endif

  OptionsSTR.FistLoad = 200;
  WriteOptionsStruct();
  //--------------------------------
  LastWritingSTR.LastAdress = GPSstartAdress;
  LastWritingSTR.WriteCount = 0;

  int LastWritingOPT_AdresTemp = LastWritingStructAdress;
  while (LastWritingOPT_AdresTemp < LastWritingStructAdress + (4 * sizeof(LastWritingStruct))) {
    eeprom_update_block((void*)&LastWritingSTR, LastWritingOPT_AdresTemp, sizeof(LastWritingStruct));
    LastWritingOPT_AdresTemp += sizeof(LastWritingStruct);
  }

  //---------------------------------
  long D = 1;
  float lat1 = 55;
  float lng1 = 45;
  int lastGPSADRTemp = GPSstartAdress;
  while (lastGPSADRTemp < 1023 - sizeof(GpsDataStruct))
  {
    GPSData.LAT = lat1;
    GPSData.LNG = lng1 ;

    GPSData.Speed = D;
    GPSData.Month = D;
    GPSData.Day = D;

    GPSData.Hour = D;
    GPSData.Min = D;
    GPSData.Sec = D;

    GPSData.StatusCode = D;

    eeprom_update_block((void*)&GPSData, lastGPSADRTemp, sizeof(GpsDataStruct));
    DEBUG_1(F("Write GPS Adress: "));  DEBUG_ln_1(lastGPSADRTemp);
    lastGPSADRTemp += sizeof(GpsDataStruct);
    D++;
    float f = (float)D / 100 + (float)D / 1000;
    lat1 = lat1 + f;
    lng1 = lng1 + f;
  }

  DEBUG_ln_1(F("FistInitial_Complite"));

  //while (1) delay(100000000);
}


void LoadFullOptions() {
  LoadOptions();
  PrintFull_Options();
  DEBUG_ln_1(F("========================"));
  //---------------------------------

  int lastGPSADRTemp = GPSstartAdress;
  while (lastGPSADRTemp < 1023 - sizeof(GpsDataStruct))
  {
    ReadGPSDataTO_CONST(lastGPSADRTemp);

    DEBUG_ln_1(lastGPSADRTemp);
    DEBUG_ln_1(GPSData.LAT);
    DEBUG_ln_1(GPSData.LNG);

    DEBUG_ln_1(GPSData.Speed);
    DEBUG_ln_1(GPSData.Month);
    DEBUG_ln_1(GPSData.Day);

    DEBUG_ln_1(GPSData.Hour);
    DEBUG_ln_1(GPSData.Min);
    DEBUG_ln_1(GPSData.Sec);

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }

  DEBUG_ln_1(F("FistInitial Test_Complite"));

  // while (1) delay(100000000);
}

void ReadGPSDataTO_CONST(int adress) {
  eeprom_read_block((void*)&GPSData, adress, sizeof(GpsDataStruct));
}

#endif

#ifdef TestFunctions

void Test_WR_Data()
{
  for (int i = 0; i < 100; i++) {
    GpsDataStruct DataTemp;

    DataTemp.LAT = i;
    DataTemp.LNG = i;

    DataTemp.Speed = i;

    DataTemp.Month = i;
    DataTemp.Day = i;

    DataTemp.Hour = i;
    DataTemp.Min = i;
    DataTemp.Sec = i;

    DataTemp.StatusCode = 0;

    WriteGPSData(DataTemp);
  }

  DEBUG_ln_1(F("-----------------------------------------"));

  LoadOptions(); //загрузить опции из ROM
  PrintFull_Options();//выводим в консоль все опции
  PrintlnFull_GPS_Data(); //выводим все данные GPS

  while (1) delay(1000000);

}

#endif
