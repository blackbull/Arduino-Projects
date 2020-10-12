
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




void PrintlnFull_GPS_Data() {

  GpsDataStruct GPSDataTemp;
  int lastGPSADRTemp = LastWritingSTR.LastAdress + sizeof(GpsDataStruct);

  String ret;
  int CountOUT = 0;//считаем количество строк, тк более 30 вывести оперативки не хватит
  while (lastGPSADRTemp < 1023)//считываем все старые координаты до конца памяти
  {
    GPSDataTemp = ReadGPSData(lastGPSADRTemp);
    // Print_GPS_Data(GPSDataTemp, lastGPSADRTemp);
    ret += GPS_Data_ToString(GPSDataTemp) + "\n";

    CountOUT++;
    if (CountOUT >= 10) {
      Serial.println(ret); //выводим накопившееся
      CountOUT = 0; //обнуляем счетчик и переменную вывода
      ret = "";
    }

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }

  lastGPSADRTemp = GPSstartAdress; //считываем до последней записи

  while (lastGPSADRTemp <= LastWritingSTR.LastAdress)//считываем до последней записи
  {
    GPSDataTemp = ReadGPSData(lastGPSADRTemp);
    //Print_GPS_Data(GPSDataTemp, lastGPSADRTemp);
    ret +=  GPS_Data_ToString(GPSDataTemp) + "\n";

    CountOUT++;
    if (CountOUT >= 10) {
      Serial.println(ret); //выводим накопившееся
      CountOUT = 0; //обнуляем счетчик и переменную вывода
      ret = "";
    }

    lastGPSADRTemp += sizeof(GpsDataStruct);
  }
  Serial.println(ret); //выводим остатки
}

void Print_GPS_Data(GpsDataStruct Data, int Adress) { //вывести в консоль GPS данные

  Serial.println(Adress);
  Serial.println(Data.LAT);
  Serial.println(Data.LNG);

  Serial.println(Data.Speed);
  Serial.println(Data.Month);
  Serial.println(Data.Day);

  Serial.println(Data.Hour);
  Serial.println(Data.Min);
  Serial.println(Data.Sec);
}

String GPS_Data_ToString(GpsDataStruct Data) {
  char sd[22];
  sprintf(sd, "%03dKmH %02d/%02d,%02d:%02d:%02d", Data.Speed, Data.Day, Data.Month, Data.Hour, Data.Min, Data.Sec);

  char LAT[10];
  char LNG[10];
  dtostrf(Data.LAT, 4, 4, LAT);
  dtostrf(Data.LNG, 4, 4, LNG);

  return String( LAT) + "," + String( LNG) + "," + String(sd);
}


void WriteOptionsStruct() {
  Serial.println("WriteOptionsStruct");
  eeprom_update_block((void*)&OptionsSTR, OptionsStructAdress, sizeof(OptionsStruct));
}

void WriteLastWritingStruct() {
  if (LastWritingSTR.WriteCount >=  OptionsSTR.MaxWriteCount) { //превысили разрешенное количество записей на ячейку
    Serial.println("Previsili Max Whiting Per Bait");

    LastWritingSTR.WriteCount = 0;
    OptionsSTR.LastWritingOPT_Adres += sizeof(LastWritingStruct);

    if (OptionsSTR.LastWritingOPT_Adres >= LastWritingStructAdress + (4 * sizeof(LastWritingStruct))) { //выработали все разрешенные ячейки, начинаем заново
      Serial.println("Reload From Start");
      OptionsSTR.LastWritingOPT_Adres = LastWritingStructAdress;
    }

    WriteOptionsStruct();//перезаписываем опции тк адрес ячейки изменился
  }

  eeprom_update_block((void*)&LastWritingSTR, OptionsSTR.LastWritingOPT_Adres, sizeof(LastWritingStruct));
}

void WriteGPSData(GpsDataStruct Data) {
  if (LastWritingSTR.LastAdress + sizeof(GpsDataStruct) > 1023) { //достигли конца ячеек ROM начинаем заново
    LastWritingSTR.LastAdress = GPSstartAdress;
  }
  else {
    LastWritingSTR.LastAdress += sizeof(GpsDataStruct);
  }

  LastWritingSTR.WriteCount++;

  WriteLastWritingStruct();//записываем обновление последнего адреса в спец структуру
  eeprom_update_block((void*)&Data, LastWritingSTR.LastAdress, sizeof(GpsDataStruct)); //записываем данные
}
