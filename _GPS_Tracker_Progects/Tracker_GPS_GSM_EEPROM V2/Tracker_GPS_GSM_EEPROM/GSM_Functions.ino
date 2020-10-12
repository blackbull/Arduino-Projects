

void CheckGSM_RING() {

  if (SIM800.available())   {                         // Если модем, что-то отправил...
    _response = waitResponse();                       // Получаем ответ от модема для анализа
    _response.trim();                                 // Убираем лишние пробелы в начале и конце
    DEBUG_ln_2(_response);                        // Если нужно выводим в монитор порта
    //if (_response.indexOf("+CMTI:") > -1) {           // Пришло сообщение об отправке SMS
    // lastUpdate = millis() -  updatePeriod;          // Теперь нет необходимости обрабатываеть SMS здесь, достаточно просто
    // сбросить счетчик автопроверки и в следующем цикле все будет обработано
    // }


    if (_response.startsWith(F("RING"))) {         // Есть входящий вызов
      int phoneindex = _response.indexOf(F("+CLIP: \""));// Есть ли информация об определении номера, если да, то phoneindex>-1
      String innerPhone = "";                   // Переменная для хранения определенного номера
      if (phoneindex >= 0) {                    // Если информация была найдена
        phoneindex += 8;                        // Парсим строку и ...
        innerPhone = _response.substring(phoneindex, _response.indexOf("\"", phoneindex)); // ...получаем номер
        DEBUG_ln_2("Number: " + innerPhone); // Выводим номер в монитор порта


        sendATCommand(F("ATH"), true);        // отклоняем вызов
        // Проверяем, чтобы длина номера была больше 6 цифр, и номер должен быть в списке
        if (innerPhone.length() >= 7 && Phones.indexOf(innerPhone) >= 0) {
          Send_GPS_Link_in_SMS(innerPhone);// Если да, то отвечаем смс
        }
        else { //если номер не удалось определить, возможно отключен определитель номера => слетела инициализация GSM
          InitialGSMFlag = false; //сбрасываем флаг инициализации, для переинициализации
          DEBUG_ln_1(F("InitialGSMFlag = false in RING loop"));
        }
      }
    }
  }
}

void Check_Wait_ToSend_NewGPS_position() { //функция отправки свежих GPS по запросу
  if (WaitNewGPS_position) {
    if (FreshGPSData) {
      WaitNewGPS_position = false;
      Send_GPS_Link_in_SMS( Wait_Ansver_Phone);
      Wait_Ansver_Phone = "";
    }
    else if (WaitNewGPS_position_Timer.isReady()) {
      WaitNewGPS_position = false;
      Send_GPS_Link_in_SMS( Wait_Ansver_Phone);
      Wait_Ansver_Phone = "";
    }
  }
}

void Check_Wait_ToSend_History_GPS_position() { //функция отправки свежих GPS по запросу
  if (History_GPS_Data_NeedCount > 0) {
    DEBUG_ln_2(F("Create History GPS Data"));

    byte count = 0;
    byte j = 0;
    for (byte i = 0; i < History_GPS_Data_NeedCount; i++) {
      if (j == 0) sendSMS_Start(Wait_Ansver_Phone);

      sendSMS_AddText(Get_Last_GPS_Data_String(1, count));
      count++;
      j++;

      if (j == 8 || i == History_GPS_Data_NeedCount - 1) {
        j = 0;
        sendSMS_Stop();
      }
    }

    History_GPS_Data_NeedCount = 0; //сбрасываем запрос на историю GPS
    Wait_Ansver_Phone = "";
  }
}




//отправка AT команд
String sendATCommand(String cmd, bool waiting) {
  String _resp = "";                                              // Переменная для хранения результата
  // DEBUG_3(F("=> Send: ")); DEBUG_ln_3(cmd);                         // Дублируем команду в монитор порта
  SIM800.println(cmd);                                            // Отправляем команду модулю
  if (waiting) {                                                  // Если необходимо дождаться ответа...
    _resp = waitResponse();                                       // ... ждем, когда будет передан ответ
    // Если Echo Mode выключен (ATE0), то эти 3 строки можно закомментировать
    // if (_resp.startsWith(cmd)) {                                  // Убираем из ответа дублирующуюся команду
    // _resp = _resp.substring(_resp.indexOf("\r", cmd.length()) + 2);
    //  }
    // DEBUG_3(F("<= Answer: ")); DEBUG_ln_3(_resp);                    // Дублируем ответ в монитор порта
  }
  return _resp;                                                   // Возвращаем результат. Пусто, если проблема
}

String waitResponse() {                                           // Функция ожидания ответа и возврата полученного результата
  String _resp = "";                                              // Переменная для хранения результата
  long _timeout = millis() + 10000;                               // Переменная для отслеживания таймаута (10 секунд)
  while (!SIM800.available() && millis() < _timeout)  {};         // Ждем ответа 10 секунд, если пришел ответ или наступил таймаут, то...
  if (SIM800.available()) {                                       // Если есть, что считывать...
    _resp = SIM800.readString();                                  // ... считываем и запоминаем
  }
  else {                                                          // Если пришел таймаут, то...
    DEBUG_ln_2(F("Timeout..."));                                 // ... оповещаем об этом и...
  }
  return _resp;                                                   // ... возвращаем результат. Пусто, если проблема
}
