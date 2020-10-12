String phones = "111111111111_222222222222_333333333333";   // Белый список телефонов
int pins[3] = {4, 5, 6};                                      // Пины с подключенными светодиодами

void setup() {
  Serial.begin(9600);
  Serial.println(F("======================================================================================="));

  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);                                 // Настраиваем пины в OUTPUT
    digitalWrite(pins[i], 1);                                 //выключаем светодиоды
  }

  DoSMS_Command ("setadm02+79998887766", "+79527801280");
  Serial.println(F("-------------------"));
  DoSMS_Command("setadm03+79998887766", "+79527801280");
  Serial.println(F("-------------------"));
  DoSMS_Command("setadm03+79527801280", "+79998887766");
  Serial.println(F("-------------------"));
  Serial.println(F("-------------------"));

  DoSMS_Command("led03", "+79998887766");
  Serial.println(F("-------------------"));
  DoSMS_Command("led   03", "+79998887766");
  Serial.println(F("-------------------"));
  // DoSMS_Command("led...11", "+79998887766");
  // Serial.println(F("-------------------"));
  DoSMS_Command("setled21", "+79527801280");
  Serial.println(F("-------------------"));
  DoSMS_Command("getopt", "+79527801280");
  Serial.println(F("-------------------"));
  DoSMS_Command("getad", "+79527801280");
}

void loop() {
  // put your main code here, to run repeatedly:

}



void DoSMS_Command (String sms, String phone) {
  bool NeedAnswer = false;
  bool CorrectCommand = false;
  String Answer = "Incorrect Command: " + sms;
  sms.toLowerCase();

  String Name = sms.substring(0, 6);
  int Numb = sms.substring(6, 8).toInt();

  Serial.println(Name);
  Serial.println(Numb);

  //=================установка админов==================================
  if (phones.indexOf(phone) > -1 || phones.indexOf("111111111111_222222222222_333333333333") > -1) //если смс отправлено с админского номера или админов ещё не установлено
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
  Serial.println(Answer);                // Статус исполнения
  if (NeedAnswer) {
    //отправить ответное смс
  }
}


String GetAllOptions () {
  return "Admin numbers: " + phones + "\nSomethig other options";
}
