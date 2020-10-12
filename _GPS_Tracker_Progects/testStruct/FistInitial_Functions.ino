#ifdef FistInitial
void InitializingOptions() {
  Phones = "111111111111_222222222222_333333333333";
  SavePhones();

  OptionsSTR.SleepMode = 0;
  OptionsSTR.LastWritingOPT_Adres = LastWritingStructAdress;
  OptionsSTR.MaxWriteCount = 1000000;
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
  float lat1 = 56.2725;
  float lng1 = 43.9817;
  int lastGPSADRTemp = GPSstartAdress;
  while (lastGPSADRTemp < 1023)
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
    lastGPSADRTemp += sizeof(GpsDataStruct);
    D++;
    float f = (float)D / 100 + (float)D / 1000;
    lat1 = 56.2725 + f;
    lng1 = 43.9817 + f;
  }

  Serial.println("FistInitial_Complite");

  //while (1) delay(100000000);
}


void LoadFullOptions() {
  LoadPhones();
  Serial.println(Phones);
  eeprom_read_block((void*)&OptionsSTR, OptionsStructAdress, sizeof(OptionsStruct)); //основные опции

  Serial.println(OptionsSTR.SleepMode);
  Serial.println(OptionsSTR.LastWritingOPT_Adres);
  Serial.println(OptionsSTR.MaxWriteCount);
  Serial.println(OptionsSTR.FistLoad);
  Serial.println("===================");
  //--------------------------------

  int LastWritingOPT_AdresTemp = LastWritingStructAdress;
  while (LastWritingOPT_AdresTemp < LastWritingStructAdress + (4 * sizeof(LastWritingStruct))) {

    eeprom_update_block((void*)&LastWritingSTR, LastWritingOPT_AdresTemp, sizeof(LastWritingStruct));

    Serial.println(LastWritingOPT_AdresTemp);
    Serial.println(LastWritingSTR.LastAdress);
    Serial.println(LastWritingSTR.WriteCount);
    Serial.println("------------------");

    LastWritingOPT_AdresTemp += sizeof(LastWritingStruct);
  }
  Serial.println("===================");
  //---------------------------------

  int lastGPSADRTemp = GPSstartAdress;
  while (lastGPSADRTemp < 1023)
  {
    ReadGPSDataTO_CONST(lastGPSADRTemp);

    Serial.println(lastGPSADRTemp);
    Serial.println(GPSData.LAT);
    Serial.println(GPSData.LNG);

    Serial.println(GPSData.Speed);
    Serial.println(GPSData.Month);
    Serial.println(GPSData.Day);

    Serial.println(GPSData.Hour);
    Serial.println(GPSData.Min);
    Serial.println(GPSData.Sec);

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }

  Serial.println("FistInitial Test_Complite");

  // while (1) delay(100000000);
}

void ReadGPSDataTO_CONST(int adress) {
  eeprom_read_block((void*)&GPSData, adress, sizeof(GpsDataStruct));
}

#endif
