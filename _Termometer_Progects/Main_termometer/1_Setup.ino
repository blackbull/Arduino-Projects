void setup() {
  Serial.begin(9600);

  //включаем питание приемника
  pinMode(PowerPinRX, OUTPUT);
   digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);
  //включаем питание термометра
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);



  nextTime = millis();
  sleepTime = millis();

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);

  //eeprom_update_block((void*)&Bad, 1, sizeof(int));

  //eeprom_read_block((void*)&Bad, 1, sizeof(int));

  //-------------------------Экран-----------------------------

  // Wire.begin();
  //Wire.setClock(400000L);

  myOLED.begin(); //инициализируем дисплей

  myOLED.clrScr();                                          //Очищаем буфер дисплея.
  myOLED.setFont(SmallFont);                               //Перед выводом текста необходимо выбрать шрифт
  myOLED.print("    IN        OUT", 0, 0);

  myOLED.print("O", 45, 10);
  myOLED.print("%", 45, 40);
  myOLED.update();

  Serial.println(F("Oled OK"));

  //-----------------------термометр------------------
  if (! bme.begin(0x76, &Wire)) {
    Serial.println(F("sensor problem!"));
    while (1);
  }
  Serial.println(F(" BME280 OK"));

  //------------------------------настройка приемника--------------------
  vw_set_rx_pin(RxPin);
  vw_setup(2000);
  vw_rx_start();

  attachInterrupt(1, getSignal, CHANGE);      //прием на прерываниях

  Serial.println(F("================================"));
}

void getSignal()
{
  //данные приходят по одному байту, поэтому обработка на прерываниях

  if (vw_get_message(message, &messageLength))
  {
    for (int i = 0; i < messageLength; i++)
    {
      char c = message[i];
      Message += c;
      // Serial.println(c);

      if (c == 's') //символ начала передачи
      {
        //начало передачи
        nextTime = millis() + 2000; //подправляем время окончания передачи
        count = 1;
      }

      else if (c == 'd')
      {
        count++;
      }
      else if (c == 'e') //символ окончания передачи
      {
        sleepTime = millis() + 8500; //приняли конечные данные нормально, засыпаем до следующей передачи

        mode = 3;
        count++;
      }
    }
  }
}
