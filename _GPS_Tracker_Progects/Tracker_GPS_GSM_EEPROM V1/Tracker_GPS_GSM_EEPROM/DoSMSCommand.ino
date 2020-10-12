void DoSMS_Command (String sms, String phone) {
  bool NeedAnswer = false;
  bool CorrectCommand = false;
  String Answer = "Incorrect Command: " + sms;
  sms.toLowerCase();

  String Name = sms.substring(0, 6);
  int Numb = sms.substring(6, 8).toInt();

  DEBUG_ln_3(Name);
  DEBUG_ln_3(Numb);

  //=================установка админов==================================
  if (Phones.indexOf(phone) > -1 || Phones.indexOf(F("111111111111_222222222222_333333333333")) > -1) //если смс отправлено с админского номера или админов ещё не установлено
  {
    if (Name == F("setadm")) {

      CorrectCommand = true; //команда расшифрована успешно

      if (Numb > 0) {
        String NewPhone = sms.substring(8, 20);
        if (NewPhone.length() != 12) {//длинна номера должна быть 12 символов, иначе команда не будет приниматься
          Answer = F("Incorrect Admin Number. Primer: \"setadm01+79998887766\"");
          NeedAnswer = true;
        }
        else {
          switch (Numb) {
            case 1:
              Phones.replace(Phones.substring(0, 12), NewPhone);
              Answer = GetAllOptions();
              break;
            case 2:
              Phones.replace(Phones.substring(13, 25), NewPhone);
              Answer = GetAllOptions();
              break;
            case 3:
              Phones.replace(Phones.substring(26, 38), NewPhone);
              Answer = GetAllOptions();
              break;
            default:
              Answer = F("Incorrect Admin Number. Primer: \"setadm01+79998887766\"");
              NeedAnswer = true;
              break;
          }

          SavePhones(); //сохраняем измененные админские номера
        }
      }
    }
  }

  //=================остальные команды==================================
  if (!CorrectCommand)  //если команда установки админа уже была выполнена
  {
    if (Phones.indexOf(phone) > -1 ) //если смс отправлено с админского номера
    {
      if (Name.indexOf(F("last04")) > -1 && !CorrectCommand) { //прислать ПОСЛЕДНИЕ 8 координат, с пропуском нескольких свежих
        CorrectCommand = true; //команда расшифрована успешно

        Wait_Ansver_Phone = phone;
        History_GPS_Data_NeedCount = 4; //формируем запрос истории GPS
        History_GPS_Data_SkipCount = Numb;
      }

      if (Name.indexOf(F("lastal")) > -1 && !CorrectCommand) { //прислать всю историю координат
        CorrectCommand = true; //команда расшифрована успешно

        Wait_Ansver_Phone = phone;
        History_GPS_Data_NeedCount = 63; //формируем запрос истории GPS
        History_GPS_Data_SkipCount = Numb;
      }

      if (Name.indexOf(F("where")) > -1 && !CorrectCommand) { //прислать только свежайшие координаты, возможно ожидания обновления координат, если не получится получить свежайшие, прислать последние возможные
        CorrectCommand = true; //команда расшифрована успешно
        Wait_Ansver_Phone = phone;
        WaitNewGPS_position = true;
        if (Numb == 0) WaitNewGPS_position_Timer.setTimeout(1); //отправить данные сразу же
        else WaitNewGPS_position_Timer.setTimeout(Numb * 60000);
        DEBUG_2(F("Need Fresh GPS after ")); DEBUG_ln_2(Numb);
      }

      if ((Name.indexOf(F("getopt")) > -1 || Name.indexOf(F("getadm")) > -1) && !CorrectCommand) { //отправить текущие настройки
        CorrectCommand = true; //команда расшифрована успешно
        Answer = GetAllOptions();
        NeedAnswer = true;
      }


      if (!CorrectCommand) {             //команда была некорректной, но с админского номера
        Answer = F("Incorrect Command.\nPrimer:\"setadm01+79998887766\"\n\"last0400\"");
        NeedAnswer = true;
      }
    }
    else {
      Answer = F("No admin");    //СМС пришло от нмера не из белого списка
    }
  }


  //====================отправка ответа или отчета===================

  if (NeedAnswer) {
    sendSMS(phone, Answer);
  }
}
