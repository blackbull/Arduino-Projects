
bool has_msg_toDEL = false;                                              // Флаг наличия сообщений к удалению
void CheckAndParsingSMS() {
  byte Check_Count = 0; //счетчик попыток считывания смс

  if (millis() - lastUpdate >= updatePeriod) {                  // Пора проверить наличие новых сообщений
    do {
      Check_Count++; //инкремент счетчика
      _response = sendATCommand("AT+CMGL=\"REC UNREAD\",1", true);// Отправляем запрос чтения непрочитанных сообщений

      if (_response.indexOf("+CMGL: ") > -1) {                    // Если есть хоть одно, получаем его индекс
        int msgIndex = _response.substring(_response.indexOf("+CMGL: ") + 7, _response.indexOf("\"REC UNREAD\"", _response.indexOf("+CMGL: ")) - 1).toInt();
        char i = 0;                                               // Объявляем счетчик попыток
        do {
          i++;                                                    // Увеличиваем счетчик
          _response = sendATCommand("AT+CMGR=" + (String)msgIndex + ",1", true);  // Пробуем получить текст SMS по индексу

          _response.trim();                                       // Убираем пробелы в начале/конце
          if (_response.endsWith("OK")) {                         // Если ответ заканчивается на "ОК"

            if (!has_msg_toDEL) has_msg_toDEL = true;             // Ставим флаг наличия сообщений для удаления
            sendATCommand("AT+CMGR=" + (String)msgIndex, true);   // Делаем сообщение прочитанным

            // sendATCommand("\n", true);                            // Перестраховка - вывод новой строки (по факту ожидаем TimeOUT, не надо нам этого)
            parseSMS(_response);                                  // Отправляем текст сообщения на обработку
            break;                                                // Выход из do{}
          }
          else {                                                  // Если сообщение не заканчивается на OK
            DEBUG_ln_2(F("Error answer"));                      // Какая-то ошибка
            sendATCommand("\n", true);                            // Отправляем новую строку и повторяем попытку
          }
        } while (i < 3);
        break;
      }
      else {
        _response.trim();                                       // Убираем пробелы в начале/конце
        if (!_response.endsWith("OK")) {                         // Если ответ НЕ заканчивается на "ОК"
          InitialGSMFlag = false; //какие то проблемы с получением данных, перезагрузим GSM модуль
          DEBUG_ln_1(F("InitialGSMFlag = false"));
        }
        lastUpdate = millis();                                    // Обнуляем таймер
        if (has_msg_toDEL) {
          sendATCommand("AT+CMGDA=\"DEL READ\"", true);           // Удаляем все прочитанные сообщения
          has_msg_toDEL = false;
        }
        break;
      }
    } while (Check_Count < 3);

    lastUpdate = millis();  // Обнуляем таймер
  }
}

void parseSMS(String msg) {                                   // Парсим SMS
  DEBUG_ln_3(F("parsing SMS"));

  String msgheader  = "";
  String msgbody    = "";
  String msgphone   = "";

  msg = msg.substring(msg.indexOf("+CMGR: "));
  msgheader = msg.substring(0, msg.indexOf("\r"));            // Выдергиваем телефон

  msgbody = msg.substring(msgheader.length() + 2);
  msgbody = msgbody.substring(0, msgbody.lastIndexOf("OK"));  // Выдергиваем текст SMS
  msgbody.trim();

  int firstIndex = msgheader.indexOf("\",\"") + 3;
  int secondIndex = msgheader.indexOf("\",\"", firstIndex);
  msgphone = msgheader.substring(firstIndex, secondIndex);

  DEBUG_ln_2("Phone: " + msgphone);                       // Выводим номер телефона
  DEBUG_ln_2("Message: " + msgbody);                      // Выводим текст SMS

  if (msgphone.length() > 6 && phones.indexOf(msgphone) > -1) { // Если телефон в белом списке, то...
    DoSMS_Command(msgbody, msgphone);                           // ...выполняем команду
  }
  else {
    DEBUG_ln_2(F("Unknown phonenumber"));
  }
}
