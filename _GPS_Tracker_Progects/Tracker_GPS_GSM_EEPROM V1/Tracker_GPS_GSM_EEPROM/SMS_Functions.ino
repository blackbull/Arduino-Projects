

void CheckAndParsingSMS() {
  byte Check_Count = 0; //счетчик попыток считывания смс

  if (SMSReadTimer.isReady()) {                  // Пора проверить наличие новых сообщений

    for (int msgIndex = 1; msgIndex <= 10; msgIndex++) { //проходим по всем ячейкам СМС
      Check_Count++; //инкремент счетчика

      DEBUG_3(F("Check Read SMS #")); DEBUG_ln_3(msgIndex);
      _response = sendATCommand("AT+CMGR=" + (String)msgIndex + ",1", true); //запрашиваем СМС из ячейки
      DEBUG_ln_3(F("_response"));
      DEBUG_ln_3(_response);

      _response.trim();                                       // Убираем пробелы в начале/конце
      if (_response.endsWith("OK")) {
        if (_response.indexOf("+CMGR: ") > -1 && _response.indexOf("REC UNREAD") > -1) { //если сообщение прочиталось и не было прочитано ранее
          DEBUG_ln_3(F("SMS read OK and REC UNREAD"));
          Check_Count = 0;
          parseSMS(_response);                                  // Отправляем текст сообщения на обработку
        }

        sendATCommand("AT+CMGR=" + (String)msgIndex, true);   // Делаем сообщение прочитанным
      }
      else {                                                 // Если сообщение не заканчивается на OK

        if (_response.indexOf("RING") > -1) {
          DEBUG_ln_2(F("Have RING, Check SMS cansel"));
          return; //нам звонят, откладываем проверку смс
        }

        DEBUG_ln_2(F("Error answer"));                      // Какая-то ошибка
        sendATCommand("\n", true);                            // Отправляем новую строку и повторяем попытку

        if (Check_Count < 2) {
          DEBUG_ln_1(F("-Repeat read SMS; CheckAndParsingSMS"));
          msgIndex--;
        }
        if (Check_Count == 2) { //уже 2 попытки считывания смс прошли, возможно проблемы в инициализации модуля
          DEBUG_ln_1(F("-InitialGSM; CheckAndParsingSMS"));
          InitialGSM();  //какие то проблемы с получением данных, перезагрузим GSM модуль
          msgIndex--;
        }
        if (Check_Count >= 3) { //после пере-инициализации смс так и не считалось, удаляем его нафиг
          DEBUG_ln_1(F("Cant read SMS, DEL nafig; CheckAndParsingSMS"));

          sendATCommand("AT+CMGR=" + (String)msgIndex, true);   // Делаем сообщение прочитанным
          // sendATCommand("AT+CMGDA=\"DEL READ\"", true);           // Удаляем все прочитанные сообщения
        }
      }

    }

    sendATCommand("AT+CMGDA=\"DEL READ\"", true);           // Удаляем все прочитанные сообщения
    DEBUG_ln_2(F("ALL SMS read, DEL"));
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

  if (msgphone.length() >= 12) { // Если телефон не короткий, нормально расшифровался то
    DoSMS_Command(msgbody, msgphone);                           // ...выполняем команду
  }
  else {
    DEBUG_ln_2(F("Bad phonenumber"));
  }
}



String GetAllOptions () {
  return "Admin numbers: " + Phones + "\nSomethig other options";
}


String Get_GPS_Link()
{
  String ret = "http://maps.google.com/maps?q=loc:";
  char sd[22];
  char LAT[10];
  char LNG[10];
  char Vcc[5];
  char Bat[5];
  dtostrf( GetVccVolt(), 2, 1, Vcc);
  dtostrf( GetBatVolt(), 2, 1, Bat);

  if (FreshGPSData) {
    sprintf(sd, "KmH %02d/%02d,%02d:%02d:%02d HDOP %02d",  Fresh_date.day(), Fresh_date.month(), Fresh_time.hour(), Fresh_time.minute(), Fresh_time.second(), Fresh_HDOP);
    dtostrf(Fresh_LAT, 4, 4, LAT);
    dtostrf(Fresh_LNG, 4, 4, LNG);
    ret += String( LAT) + "," + String( LNG) + " " + String(Fresh_Speed) + String(sd) + F(" NOW ") + F("Bat ") + String(Bat) + F(" Vcc ") + String(Vcc);
  }
  else
  {
    sprintf(sd, "KmH %02d/%02d,%02d:%02d:%02d",  GPSData.Day, GPSData.Month, GPSData.Hour, GPSData.Min, GPSData.Sec);
    dtostrf(GPSData.LAT, 4, 4, LAT);
    dtostrf(GPSData.LNG, 4, 4, LNG);
    ret += String( LAT) + "," + String( LNG) + " " + String(GPSData.Speed) + String(sd) + F(" LAST ") + F("Bat ") + String(Bat) + F(" Vcc ") + String(Vcc);
  }

  return ret;
}

void sendSMS(String phone, String message) {
  sendSMS_Start(phone);
  sendSMS_AddText(message);
  sendSMS_Stop();
}

void sendSMS_Start(String phone) {

#ifdef SendSMS
  digitalWrite(GSM_DTR_pin, HIGH); //отключаем энергосбережение

  sendATCommand("AT+CMGS=\"" + phone + "\"", true);             // Переходим в режим ввода текстового сообщения
#endif
  DEBUG_1(F("Start SMS to: ")); DEBUG_ln_1(phone);

}

void sendSMS_AddText(String message) {

#ifdef SendSMS
  sendATCommand(message, false);             // набиваем текст в сообщение
#endif
  DEBUG_1(F("Add text: ")); DEBUG_ln_1(message);

}


void sendSMS_Stop() {

#ifdef SendSMS
  sendATCommand((String)((char)26), true);   // После текста отправляем перенос строки и Ctrl+Z
  digitalWrite(GSM_DTR_pin, LOW); //включаем энергосбережение
#endif
  DEBUG_ln_1(F("Send SMS Stop "));

}
