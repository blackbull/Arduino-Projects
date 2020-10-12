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
  if (phones.indexOf(phone) > -1 || phones.indexOf(F("111111111111_222222222222_333333333333")) > -1) //если смс отправлено с админского номера или админов ещё не установлено
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
              phones.replace(phones.substring(0, 12), NewPhone);
              Answer = GetAllOptions();
              break;
            case 2:
              phones.replace(phones.substring(13, 25), NewPhone);
              Answer = GetAllOptions();
              break;
            case 3:
              phones.replace(phones.substring(26, 38), NewPhone);
              Answer = GetAllOptions();
              break;
            default:
              Answer = F("Incorrect Admin Number. Primer: \"setadm01+79998887766\"");
              NeedAnswer = true;
              break;
          }
        }
      }
    }
  }

  //=================остальные команды==================================
  if (!CorrectCommand)  //если команда установки админа уже была выполнена
  {
    if (phones.indexOf(phone) > -1 ) //если смс отправлено с админского номера
    {
      if (Name.indexOf(F("led")) > -1 && !CorrectCommand) { //включить светодиод
        CorrectCommand = true; //команда расшифрована успешно
        switch (Numb) {
          case 10:
            digitalWrite(pins[0], 1);
            Answer = F("Led 1 OFF");
            break;
          case 20:
            digitalWrite(pins[1], 1);
            Answer = F("Led 1 OFF");
            break;
          case 30:
            digitalWrite(pins[2], 1);
            Answer = F("Led 1 OFF");
            break;
          case 11:
            digitalWrite(pins[0], 0);
            Answer = F("Led 1 ON");
            break;
          case 21:
            digitalWrite(pins[1], 0);
            Answer = F("Led 2 ON");
            break;
          case 31:
            digitalWrite(pins[2], 0);
            Answer = F("Led 3 ON");
            break;


          default:
            Answer = F("Incorrect LED Number. Primer: \"led...11\", \"ledzzz11\"");
            NeedAnswer = true;
            break;
        }
      }

      if ((Name.indexOf(F("getopt")) > -1 || Name.indexOf(F("getadm")) > -1) && !CorrectCommand) { //отправить текущие настройки
        CorrectCommand = true; //команда расшифрована успешно
        Answer = GetAllOptions();
        NeedAnswer = true;
      }


      if (!CorrectCommand) {             //команда была некорректной, но с админского номера
        Answer = F("Incorrect Command.\nPrimer:\"setadm01+79998887766\"\n\"led...11\"");
        NeedAnswer = true;
      }
    }
    else {
      Answer = F("No admin");    //СМС пришло от нмера не из белого списка
    }
  }


  //====================отправка ответа или отчета===================
  DEBUG_ln_2(Answer);                // Статус исполнения
  if (NeedAnswer) {
    //отправить ответное смс
  }
}
