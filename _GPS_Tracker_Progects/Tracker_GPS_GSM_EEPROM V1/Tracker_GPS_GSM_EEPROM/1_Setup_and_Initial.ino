void setup()
{
  SIM800.begin(9600);  // включаем порт для инициализации
#ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
  Serial.begin(9600);
#endif
  DEBUG_ln_1(F("======================================================================"));

  //-------------Voltmetr-------------------------
  pinMode(pinBat, INPUT);
  pinMode(pinVcc, INPUT);
  DEBUG_2(F("Bat: ")); DEBUG_2(GetBatVolt());
  DEBUG_2(F(" Vcc: ")); DEBUG_ln_2(GetVccVolt());
  //---------------------------------------------------

#ifdef DEBUG_1_ENABLE
  //зажигаем светодиод, что GPS получен
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);
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
  //загружаем последние данные в переменные для сравнения новых
  last_Add_LAT = GPSData.LAT;
  last_Add_LNG = GPSData.LNG;


#ifdef TestFunctions
  Test_WR_Data();
#endif

#ifdef DEBUG_1_ENABLE
  PrintFull_Options();//выводим в консоль все опции
  PrintlnFull_GPS_Data(); //выводим все данные GPS
#endif


  pinMode(GSM_RING_pin, INPUT); //инициализируем пин RING
  pinMode(GSM_DTR_pin, OUTPUT); //инициализируем пин DTR
  digitalWrite(GSM_DTR_pin, HIGH); //отключаем энергосбережение на время инициализации
  InitialGSM(); //инициализируем GSM
  digitalWrite(GSM_DTR_pin, LOW); //включаем энергосбережение

}



bool InitialGSM() {
  InitialGSMFlag = false;
  DEBUG_ln_2("InitialGSM -> Start");

  String ans = sendATCommand("AT", true);
  ans.trim();
  if ( ans.endsWith("OK"))      // Отправили AT для настройки скорости обмена данными
  {
    //sendATCommand("AT+CMGDA=\"DEL ALL\"", true);               // Удаляем все SMS, чтобы не забивать память

    // Команды настройки модема при каждом запуске
    sendATCommand("ATE0", true);                                //ывключаем ЭХО
    sendATCommand("AT+CLIP=1", true);                           // Включаем АОН
    //_response = sendATCommand("AT+DDET=1", true);             // Включаем DTMF
    // sendATCommand("AT+CPMS=SM,SM,SM", true);                  //установить память для сохранения смс -> сим карта
    sendATCommand("AT+CNMI=1,0", true);                       //не выводить сообщение о пришедших смс, а сразу сохранять их в сим
    sendATCommand("AT+CMGF=1", true);                        // Включаем текстовый режима SMS (Text mode) и сразу сохраняем значение (AT&W)(не сохраняем, что бы не расходовать ресурс памяти)!
    InitialGSMFlag = true;

    DEBUG_ln_2(F(" InitialGSM -> OK"));
  }
  else DEBUG_ln_1(F(" InitialGSM -> ERROR"));

  return InitialGSMFlag;
}
