

void CheckAndParsingSMS() {
  byte Check_Count = 0; //счетчик попыток считывания смс

  if (SMSReadTimer.isReady()) {                  // Пора проверить наличие новых сообщений

    while (Check_Count <= 4)
    {
      Check_Count++; //инкремент счетчика

      DEBUG_3(F("Check Read SMS #")); DEBUG_ln_3(msgIndex);
      _response = sendATCommand("AT+CMGR=" + (String)msgIndex + ",1", true); //запрашиваем СМС из ячейки
      DEBUG_ln_3(F("_response"));
      DEBUG_ln_3(_response);

      _response.trim();                                       // Убираем пробелы в начале/конце
      if (_response.endsWith(F("OK"))) {
        if (_response.indexOf(F("+CMGR: ")) > -1 && _response.indexOf(F("REC UNREAD")) > -1) { //если сообщение прочиталось и не было прочитано ранее
          DEBUG_ln_3(F("SMS read OK and REC UNREAD"));
          Check_Count = 0;
          parseSMS(_response);                                  // Отправляем текст сообщения на обработку
        }

        sendATCommand("AT+CMGR=" + (String)msgIndex, true);   // Делаем сообщение прочитанным

        Check_Count = 5; //выходим из цикла
      }
      else {                                                 // Если сообщение не заканчивается на OK

        if (_response.indexOf(F("RING")) > -1) {
          DEBUG_ln_2(F("Have RING, Check SMS cansel"));
          return; //нам звонят, откладываем проверку смс
        }

        DEBUG_ln_2(F("Error answer"));                      // Какая-то ошибка
        sendATCommand("\n", true);                            // Отправляем новую строку и повторяем попытку

        if (Check_Count < 2) {
          DEBUG_ln_1(F("-Repeat read SMS; CheckAndParsingSMS"));
        }
        if (Check_Count == 2) { //уже 2 попытки считывания смс прошли, возможно проблемы в инициализации модуля
          DEBUG_ln_1(F("-InitialGSM; CheckAndParsingSMS"));
          InitialGSM();  //какие то проблемы с получением данных, перезагрузим GSM модуль
        }
        if (Check_Count >= 3) { //после пере-инициализации смс так и не считалось, удаляем его нафиг
          DEBUG_ln_1(F("Cant read SMS, DEL nafig; CheckAndParsingSMS"));

          sendATCommand("AT+CMGR=" + (String)msgIndex, true);   // Делаем сообщение прочитанным
          sendATCommand(F("AT+CMGDA=\"DEL READ\""), true);           // Удаляем все прочитанные сообщения

          Check_Count = 5; //выходим из цикла
        }
      }
    }

    msgIndex++;

    if (msgIndex > 10) {  //прошли все ячейки СМС начинаем заново
      msgIndex = 1;

      sendATCommand(F("AT+CMGDA=\"DEL READ\""), true);           // Удаляем все прочитанные сообщения
      DEBUG_ln_2(F("ALL SMS read, DEL"));
    }
  }
}



void parseSMS(String msg) {                                   // Парсим SMS
  DEBUG_ln_3(F("parsing SMS"));

  String msgheader  = F("");
  String msgbody    = F("");
  String msgphone   = F("");

  msg = msg.substring(msg.indexOf(F("+CMGR: ")));
  msgheader = msg.substring(0, msg.indexOf(F("\r")));            // Выдергиваем телефон

  msgbody = msg.substring(msgheader.length() + 2);
  msgbody = msgbody.substring(0, msgbody.lastIndexOf(F("OK")));  // Выдергиваем текст SMS
  msgbody.trim();

  int firstIndex = msgheader.indexOf(F("\",\"")) + 3;
  int secondIndex = msgheader.indexOf(F("\",\""), firstIndex);
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

/* OLD
String Get_GPS_Link()
{
  String ret = F("http://maps.google.com/maps?q=loc:");
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
*/

String Get_GPS_Link_Part1() {
  String ret = F("http://maps.google.com/maps?q=loc:");
  char LAT[10];
  char LNG[10];
  if (FreshGPSData) {
    dtostrf(Fresh_LAT, 4, 4, LAT);
    dtostrf(Fresh_LNG, 4, 4, LNG);
  }
  else {
    dtostrf(GPSData.LAT, 4, 4, LAT);
    dtostrf(GPSData.LNG, 4, 4, LNG);
  }
  ret += String( LAT) + "," + String( LNG);

  return ret;
}

String Get_GPS_Link_Part2() {
  String ret = "";
  char sd[22];
  char Vcc[5];
  char Bat[5];
  dtostrf( GetVccVolt(), 2, 1, Vcc);
  dtostrf( GetBatVolt(), 2, 1, Bat);

  if (FreshGPSData) {
    sprintf(sd, "KmH %02d/%02d,%02d:%02d:%02d HDOP %02d",  Fresh_date.day(), Fresh_date.month(), Fresh_time.hour(), Fresh_time.minute(), Fresh_time.second(), Fresh_HDOP);
    ret += String(Fresh_Speed) + String(sd) + F(" NOW ") + F("Bat ") + String(Bat) + F(" Vcc ") + String(Vcc);
  }
  else {
    sprintf(sd, "KmH %02d/%02d,%02d:%02d:%02d",  GPSData.Day, GPSData.Month, GPSData.Hour, GPSData.Min, GPSData.Sec);
    ret +=  String(GPSData.Speed) + String(sd) + F(" LAST ") + F("Bat ") + String(Bat) + F(" Vcc ") + String(Vcc);
  }
  return ret;
}


void Send_GPS_Link_in_SMS(String phone) {
  sendSMS_Start(phone);
  sendSMS_AddText(Get_GPS_Link_Part1());
  sendSMS_AddText(Get_GPS_Link_Part2());
  sendSMS_Stop();
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
