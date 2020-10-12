void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);                                 // Настраиваем пины в OUTPUT
    digitalWrite(pins[i], 1);                                 //выключаем светодиоды
  }
#ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
  Serial.begin(9600);
#endif

  SIM800.begin(9600);                                         // Скорость обмена данными с модемом
  DEBUG_ln_1(F("======================================================================================="));

  InitialGSM();

  lastUpdate = millis() -  updatePeriod;                      // Обнуляем таймер
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
