void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

  if (! bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }


  delayTime = 10000;

  Wire.begin();
  Wire.setClock(400000L);


  myOLED.begin(); //инициализируем дисплей
  myOLED.clrScr();                                          //Очищаем буфер дисплея.
  myOLED.setFont(SmallFont);                               //Перед выводом текста необходимо выбрать шрифт

  myOLED.print(F("    IN        OUT"), 0, 0);

  myOLED.print(F("O"), 45, 10);
  myOLED.print(F("%"), 45, 40);

  myOLED.update();

  attachInterrupt(1, getSignal, CHANGE);      //прием на прерываниях

  Serial.println(F("================================"));
}

void getSignal() {}
