bool onFlag = true;
//------------------MAIN LOOP---------------------------------------------------------------
void loop() {

#if (USE_BTN == 1)
  static bool stepFlag = false;
  static bool brightDir = true;
  // btn.tick();
  if (enc1.isSingle()) {
    glitter = !glitter;
  }
  if (enc1.isLeft()) {
#if MY_MODE
    if (++tek_my_mode >= (my_mode_count - 1)) tek_my_mode = 0;
    newMode = pgm_read_byte(my_mode + tek_my_mode);
#else
    if (++newMode >= maxMode) newMode = 0;
#endif
    SetMode(newMode);

    myOLED.setFont(BigNumbers);
    char sd2[1];
    sprintf(sd2, "%01d", demorun);
    myOLED.print(sd2, 50, 15);
    myOLED.update();
  }
  if (enc1.isRight()) {
#if MY_MODE
    if (--tek_my_mode <= 0) tek_my_mode = my_mode_count - 1;
    newMode = pgm_read_byte(my_mode + tek_my_mode);
#else
    if (--newMode <= 256 && newMode >= 50) newMode = maxMode;
#endif
    SetMode(newMode);

    myOLED.setFont(BigNumbers);
    char sd2[1];
    sprintf(sd2, "%01d", demorun);
    myOLED.print(sd2, 50, 15);
    myOLED.update();
  }
  if (enc1.isDouble()) {
    if ( demorun == 0) demorun = 1;
    else demorun = 0;

    myOLED.setFont(BigNumbers);
    char sd2[1];
    sprintf(sd2, "%01d", demorun);
    myOLED.print(sd2, 50, 15);
    myOLED.update();
  }
  /*if (stepFlag && btn.isRelease()) {
    stepFlag = false;
    brightDir = !brightDir;
    }*/
  if (enc1.isLeftH()) {
    max_bright += 20;
    max_bright = constrain(max_bright, 0, 255);
    FastLED.setBrightness(max_bright);

    myOLED.setFont(BigNumbers);
    char sd[3];
    sprintf(sd, "%03d", max_bright);
    myOLED.print(sd, 87, 15);
    myOLED.update();
  }
  if (enc1.isRightH()) {
    max_bright -= 20;
    max_bright = constrain(max_bright, 0, 255);
    FastLED.setBrightness(max_bright);

    myOLED.setFont(BigNumbers);
    char sd[3];
    sprintf(sd, "%03d", max_bright);
    myOLED.print(sd, 87, 15);
    myOLED.update();
  }
#endif

#if ( IR_ON == 1 || KEY_ON == 1 || USE_BTN == 1 )
  getirl();                                                                   // Обработка команд с пульта и аналоговых кнопок
#endif

  if (onFlag) {
    demo_check();                                                                 // Работа если включен демонстрационный режим

    EVERY_N_MILLISECONDS(50) {                                                  // Плавный переход от одной палитры в другую
      uint8_t maxChanges = 24;
#if CHANGE_ON == 1
      if (StepMode == MAX_LEDS )
#endif
        nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, maxChanges);
    }

#if PALETTE_TIME>0
    if (palchg) {
      EVERY_N_SECONDS(PALETTE_TIME) {                                            // Смена палитры
        if (palchg == 3) {
          if (gCurrentPaletteNumber < (gGradientPaletteCount - 1))  gCurrentPaletteNumber++;
          else                                                    gCurrentPaletteNumber = 0;
#if LOG_ON == 1
          Serial.print(F("New Palette_loop: "));  Serial.println(gCurrentPaletteNumber);
#endif
        }
        gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];                // We're just ensuring that the gTargetPalette WILL be assigned.
      }
    }
#endif

#if DIRECT_TIME > 0
    EVERY_N_SECONDS(DIRECT_TIME) {                                            // Меняем направление
      thisdir = thisdir * -1;
    }
#endif

    EVERY_N_MILLIS_I(thistimer, thisdelay) {                                    // Sets the original delay time.
      thistimer.setPeriod(thisdelay);                                           // This is how you update the delay value on the fly.
      KolLed = NUM_LEDS;                                                        // Выводим Эффект на все светодиоды
      strobe_mode(ledMode, 0);                                                  // отобразить эффект;




#if CHANGE_ON == 1
      if (StepMode < NUM_LEDS) {                                                // требуется наложить новый эффект
        KolLed = StepMode;                                                      // Выводим Эффект на все светодиоды
        if (StepMode > 10)  strobe_mode(newMode, 0);                            // отобразить эффект;
#if CHANGE_SPARK == 4
        if (demorun < 1) rand_spark = 0;
        sparkler(rand_spark);
#else
        uint8_t spark = CHANGE_SPARK;
        if (demorun < 1) spark = 0;
        sparkler(spark);                                                             // бенгальский огонь
#endif
      }
#endif
    }

#if CHANGE_ON == 1
    uint8_t CHANGE_TIME_my = CHANGE_TIME;
    if (demorun < 1) CHANGE_TIME_my = 0;

    EVERY_N_MILLISECONDS(CHANGE_TIME_my * 1000 / NUM_LEDS) {                      // Движение плавной смены эффектов
      if ( StepMode < NUM_LEDS)
      { StepMode++;
        if (StepMode == 10) strobe_mode(newMode, 1);
        if (StepMode >= NUM_LEDS)
        { ledMode = newMode;
          StepMode = MAX_LEDS;
#if LOG_ON == 1
          Serial.println(F("End SetMode"));
#endif
        }
        nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, NUM_LEDS);
      }
    }
#endif

    if (glitter) addglitter(10);                                                // If the glitter flag is set, let's add some.
#if CANDLE_KOL >0
    if (candle)  addcandle();
#endif

    if (background) addbackground();                                            // Включить заполнение черного цвета фоном
  }

#if KEY_ON == 1                                                             //Для аналоговых кнопок
  key_input_new = analogRead(PIN_KEY);                                      //прочитаем аналоговые кнопки
  if  ( ( ( (key_input - KEY_DELTA) > key_input_new) ||                     //Пришло новое значение отличное от прошлого
          ( (key_input + KEY_DELTA) < key_input_new) ) &&
        !key_bounce ) {                                                     // и еще ничего не приходило
    key_bounce = 1;                                                         //Начинаем обрабатывать
    key_time = millis();                                                    //Запомним время
  }
  else if (  key_bounce &&                                                    //Обрабатываем нажатия
             ((millis() - key_time) >= 50 )  ) {                               //Закончилось время дребезга
    key_bounce = 0;                                                       //Больше не обрабатываем
    key_input = key_input_new;
#if LOG_ON == 1
    Serial.print(F("Analog Key: ")); Serial.println(key_input);
#endif

#if KEY_0 >= KEY_DELTA
    if  ( ( (KEY_0 - KEY_DELTA) < key_input) &&
          ( (KEY_0 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_0
      Protocol = 1;
      Command = KEY_0;
    }
#endif
#if KEY_1 >= KEY_DELTA
    if  ( ( (KEY_1 - KEY_DELTA) < key_input) &&
          ( (KEY_1 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_1
      Protocol = 1;
      Command = KEY_1;
    }
#endif
#if KEY_2 >= KEY_DELTA
    if  ( ( (KEY_2 - KEY_DELTA) < key_input) &&
          ( (KEY_2 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_2
      Protocol = 1;
      Command = KEY_2;
    }
#endif
#if KEY_3 >= KEY_DELTA
    if  ( ( (KEY_3 - KEY_DELTA) < key_input) &&
          ( (KEY_3 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_3
      Protocol = 1;
      Command = KEY_3;
    }
#endif
#if KEY_4 >= KEY_DELTA
    if  ( ( (KEY_4 - KEY_DELTA) < key_input) &&
          ( (KEY_4 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_4
      Protocol = 1;
      Command = KEY_4;
    }
#endif
#if KEY_5 >= KEY_DELTA
    if  ( ( (KEY_5 - KEY_DELTA) < key_input) &&
          ( (KEY_5 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_5
      Protocol = 1;
      Command = KEY_5;
    }
#endif
#if KEY_6 >= KEY_DELTA
    if  ( ( (KEY_6 - KEY_DELTA) < key_input) &&
          ( (KEY_6 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_6
      Protocol = 1;
      Command = KEY_6;
    }
#endif
#if KEY_7 >= KEY_DELTA
    if  ( ( (KEY_7 - KEY_DELTA) < key_input) &&
          ( (KEY_7 + KEY_DELTA) > key_input) )  {                       //Нашли нажатую кнопку KEY_7
      Protocol = 1;
      Command = KEY_7;
    }
#endif
  }
#endif

#if ( IR_ON == 1 || KEY_ON == 1 || USE_BTN == 1 )
  if ( (IR_Time_Mode > 0) &&                                                //Идет отчет времени
       ((millis() - IR_Time_Mode) >= 2000 )  ) {                            //И прошло больше 2 секунд
    IR_Time_Mode = 0;
    if (IR_New_Mode <= maxMode) SetMode(IR_New_Mode);
    IR_New_Mode = 0;
  }
#endif

#if IR_ON == 1
  while (!irrecv.isIdle());                                                   // if not idle, wait till complete

  if (irrecv.decode(&results)) {
    /* respond to button */

    if (!Protocol) {
      Protocol = 1;                                        // update the values to the newest valid input

#if IR_REPEAT == 1
      if ( results.value != 0xffffffff)                    //Если не повтор то вставить новую команду
        Command = results.value;
      else Protocol = 2;
#else
      Command = results.value;
#endif
    }
    irrecv.resume(); // Set up IR to receive next value.
  }
#endif

  static uint32_t showTimer = 0;
  if (onFlag && millis() - showTimer >= 10) {
    showTimer = millis();
    FastLED.show();
  }
} // loop()
