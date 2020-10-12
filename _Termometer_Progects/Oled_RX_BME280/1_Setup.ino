void setup() {
  Serial.begin(9600);

  //включаем питание приемника
  pinMode(PowerPinRX, OUTPUT);
  digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);
  //включаем питание термометра
  pinMode(PowerPinTermometr, OUTPUT);
  digitalWrite(PowerPinTermometr, HIGH);

  delay(1000);

  nextTime = millis();
  sleepTimeForNextRX = millis();
  GlobalwaitResiveTimer = millis() + 10000;

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
  myOLED.print(F("    IN        OUT"), 0, 0);

  myOLED.print(F("O"), 45, 10);
  myOLED.print(F("%"), 45, 40);
  myOLED.update();

  Serial.println(F("Oled OK"));

  //-----------------------термометр------------------
  if (! bme.begin(0x76, &Wire)) {
    while (1) {
      Serial.println(F("sensor problem!"));
      myOLED.print(F("sensor problem!"), 0, 0);
      myOLED.update();
      delay(100000);
    }
  }
  Serial.println(F(" BME280 OK"));

  //------------------------------настройка приемника--------------------
  radio.begin();                                        // Инициируем работу приёмника MX-RM-5V (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
  radio.setDataRate     (i433_1KBPS);                   // Указываем скорость приёма данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
  radio.openReadingPipe (5);                            // Открываем 5 трубу для приема данных (если вызвать функцию без параметра, то будут открыты все трубы сразу, от 0 до 7)

  radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу


  UpdateTempAndOled();

  Serial.println(F("================================"));
}
