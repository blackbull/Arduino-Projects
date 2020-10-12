

void SavePhones() {
  char ch[39];
  Phones.toCharArray(ch, 39);
  DEBUG_3("save: "); DEBUG_ln_3(ch);
  //eeprom_write_block((void*)&ch, PhonesAdress, sizeof(ch));
  EEPROM.put(PhonesAdress, ch);
}

void LoadPhones() {
  char message[39];
  EEPROM.get(PhonesAdress, message);
  //DEBUG_ln_3(message);
  //DEBUG_ln_3(String(message));
  Phones =  String(message);
  //DEBUG_ln_3(Phones);
}


void LoadOptions() {
  LoadPhones();
  eeprom_read_block((void*)&OptionsSTR, OptionsStructAdress, sizeof(OptionsStruct)); //основные опции
  eeprom_read_block((void*)&LastWritingSTR, OptionsSTR.LastWritingOPT_Adres, sizeof(LastWritingStruct));

  GPSData = Load_Last_GPS_Data();
}

GpsDataStruct Load_Last_GPS_Data() { //загрузить последние сохраненные GPS данные из eepROM
  return ReadGPSData(LastWritingSTR.LastAdress);
}

GpsDataStruct ReadGPSData(int adress) {
  GpsDataStruct GPSDataTemp;
  eeprom_read_block((void*)&GPSDataTemp, adress, sizeof(GpsDataStruct));
  return GPSDataTemp;
}

String Get_Last_GPS_Data_String(int LastCount, int Start) { //выводим максимум 16 строк, а то оперативки не хватит

  if (LastCount > 16) LastCount = 16;


  GpsDataStruct GPSDataTemp;
  int lastGPSADRTemp = LastWritingSTR.LastAdress;
  int countFull = 0; //считаем количество уже выведенных данных
  int countBreak = 0; //считаем количество уже выведенных данных
  String ret;

  while (lastGPSADRTemp >= GPSstartAdress && countFull < LastCount) //считываем все старые координаты до старта секции памяти
  {
    if (countBreak < Start) {
      countBreak++;
      lastGPSADRTemp -= sizeof(GpsDataStruct);
      continue;
    }

    GPSDataTemp = ReadGPSData(lastGPSADRTemp);
    // Print_GPS_Data(GPSDataTemp, lastGPSADRTemp);
    ret += GPS_Data_ToString(GPSDataTemp) + "\n";

    countFull++;
    lastGPSADRTemp -= sizeof(GpsDataStruct);
  }

  lastGPSADRTemp = 1017; //конечный адрес последней записи в памяти

  while (lastGPSADRTemp > LastWritingSTR.LastAdress && countFull < LastCount) //считываем до последней записи
  {
    if (countBreak < Start) {
      countBreak++;
      lastGPSADRTemp -= sizeof(GpsDataStruct);
      continue;
    }

    GPSDataTemp = ReadGPSData(lastGPSADRTemp);
    //Print_GPS_Data(GPSDataTemp, lastGPSADRTemp);
    ret +=  GPS_Data_ToString(GPSDataTemp) + "\n";

    countFull++;
    lastGPSADRTemp -= sizeof(GpsDataStruct);
  }

  return ret;
}



#ifdef DEBUG_1_ENABLE
void PrintlnFull_GPS_Data() {

  GpsDataStruct GPSDataTemp;
  int lastGPSADRTemp = LastWritingSTR.LastAdress + sizeof(GpsDataStruct);

  String ret;
  int CountOUT = 0;//считаем количество строк, тк более 30 вывести оперативки не хватит
  while (lastGPSADRTemp < 1023 - sizeof(GpsDataStruct)) //считываем все старые координаты до конца памяти
  {
    GPSDataTemp = ReadGPSData(lastGPSADRTemp);


#ifdef TestFunctions
    ret += String(lastGPSADRTemp) + " \t" + GPS_Data_ToString(GPSDataTemp) + "\n";
#else
    ret += GPS_Data_ToString(GPSDataTemp) + "\n";
#endif

    CountOUT++;
    if (CountOUT >= 10) {
      DEBUG_ln_1(ret); //выводим накопившееся
      CountOUT = 0; //обнуляем счетчик и переменную вывода
      ret = "";
    }

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }

  lastGPSADRTemp = GPSstartAdress; //считываем до последней записи

  while (lastGPSADRTemp <= LastWritingSTR.LastAdress)//считываем до последней записи
  {
    GPSDataTemp = ReadGPSData(lastGPSADRTemp);

#ifdef TestFunctions
    ret += String(lastGPSADRTemp) + " \t" + GPS_Data_ToString(GPSDataTemp) + "\n";
#else
    ret += GPS_Data_ToString(GPSDataTemp) + "\n";
#endif

    CountOUT++;
    if (CountOUT >= 10) {
      DEBUG_ln_1(ret); //выводим накопившееся
      CountOUT = 0; //обнуляем счетчик и переменную вывода
      ret = "";
    }

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }
  DEBUG_ln_1(ret); //выводим остатки
}

#endif

#ifdef DEBUG_2_ENABLE
void Print_GPS_Data(GpsDataStruct Data, int Adress) { //вывести в консоль GPS данные

  DEBUG_ln_2(Adress);
  DEBUG_ln_2(Data.LAT);
  DEBUG_ln_2(Data.LNG);

  DEBUG_ln_2(Data.Speed);
  DEBUG_ln_2(Data.Month);
  DEBUG_ln_2(Data.Day);

  DEBUG_ln_2(Data.Hour);
  DEBUG_ln_2(Data.Min);
  DEBUG_ln_2(Data.Sec);
}

#endif

String GPS_Data_ToString(GpsDataStruct Data) {
  char sd[22];
  sprintf(sd, "KmH %02d/%02d,%02d:%02d:%02d",  Data.Day, Data.Month, Data.Hour, Data.Min, Data.Sec);

  char LAT[10];
  char LNG[10];
  dtostrf(Data.LAT, 4, 4, LAT);
  dtostrf(Data.LNG, 4, 4, LNG);

  return String( LAT) + "," + String( LNG) + "," + String(Data.Speed) + String(sd);
}

#ifdef DEBUG_1_ENABLE
void PrintFull_Options() { //вывести все опции в консоль

  DEBUG_1(F("AdminPhones:  ")); DEBUG_ln_1(Phones);
  eeprom_read_block((void*)&OptionsSTR, OptionsStructAdress, sizeof(OptionsStruct)); //основные опции

  DEBUG_ln_1(F("----------Options-----------"));
  DEBUG_1(F("Options Adress: ")); DEBUG_1(OptionsStructAdress);
  DEBUG_1(F("; SleepMode: ")); DEBUG_1(OptionsSTR.SleepMode);
  DEBUG_1(F("; LastWritingOPT_Adres: ")); DEBUG_1(OptionsSTR.LastWritingOPT_Adres);
  DEBUG_1(F("; MaxWriteCount: "));  DEBUG_1(OptionsSTR.MaxWriteCount);
  DEBUG_1(F("; FistLoad: ")); DEBUG_ln_1(OptionsSTR.FistLoad);
  DEBUG_ln_1(F("----------------------------"));

  int LastWritingOPT_AdresTemp = LastWritingStructAdress;
  while (LastWritingOPT_AdresTemp < LastWritingStructAdress + (4 * sizeof(LastWritingStruct))) {

    LastWritingStruct LW_temp;

    eeprom_read_block((void*)&LW_temp, LastWritingOPT_AdresTemp, sizeof(LastWritingStruct));

    DEBUG_1(F("LW_Options Adress: ")); DEBUG_1(LastWritingOPT_AdresTemp);
    DEBUG_1(F("; GPS_LastAdress: ")); DEBUG_1(LW_temp.LastAdress);
    DEBUG_1(F("; WriteCount: ")); DEBUG_ln_1(LW_temp.WriteCount);
    DEBUG_ln_1(F("----------------------------"));

    LastWritingOPT_AdresTemp += sizeof(LastWritingStruct);
  }
}
#endif


void WriteOptionsStruct() {
  DEBUG_ln_2(F("WriteOptionsStruct"));
  eeprom_update_block((void*)&OptionsSTR, OptionsStructAdress, sizeof(OptionsStruct));
}

void WriteLastWritingStruct() {
  if (LastWritingSTR.WriteCount >=  OptionsSTR.MaxWriteCount) { //превысили разрешенное количество записей на ячейку
    DEBUG_ln_2(F("Previsili Max Whiting Per Bait"));

    LastWritingSTR.WriteCount = 0;
    OptionsSTR.LastWritingOPT_Adres += sizeof(LastWritingStruct);

    if (OptionsSTR.LastWritingOPT_Adres >= LastWritingStructAdress + (4 * sizeof(LastWritingStruct))) { //выработали все разрешенные ячейки, начинаем заново
      DEBUG_ln_2(F("Reload From Start"));
      OptionsSTR.LastWritingOPT_Adres = LastWritingStructAdress;
    }

    WriteOptionsStruct();//перезаписываем опции тк адрес ячейки изменился
  }

  DEBUG_3(F("WriteLastWritingStruct adress: ")); DEBUG_3(OptionsSTR.LastWritingOPT_Adres);
  DEBUG_3(F(" Count: ")); DEBUG_3(LastWritingSTR.WriteCount);
  DEBUG_3(F(" MaxWR: ")); DEBUG_ln_3(OptionsSTR.MaxWriteCount);

  eeprom_update_block((void*)&LastWritingSTR, OptionsSTR.LastWritingOPT_Adres, sizeof(LastWritingStruct));
}

void WriteGPSData(GpsDataStruct Data) {
  if (LastWritingSTR.LastAdress + sizeof(GpsDataStruct) > 1023 - sizeof(GpsDataStruct)) { //достигли конца ячеек ROM начинаем заново
    LastWritingSTR.LastAdress = GPSstartAdress;
  }
  else {
    LastWritingSTR.LastAdress += sizeof(GpsDataStruct);
  }

  LastWritingSTR.WriteCount++;

  WriteLastWritingStruct();//записываем обновление последнего адреса в спец структуру

  DEBUG_3(F("WriteGPSData adress: \t\t")); DEBUG_ln_3(LastWritingSTR.LastAdress);

  eeprom_update_block((void*)&Data, LastWritingSTR.LastAdress, sizeof(GpsDataStruct)); //записываем данные
}
