void loop() {

  if (InitialGSMFlag) {
    CheckGSM_RING();
    CheckAndParsingSMS();
  }
  else InitialGSM();

#ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
  if (Serial.available())  {                          // Ожидаем команды по Serial...
    SIM800.write(Serial.read());                      // ...и отправляем полученную команду модему
  };
#endif
}
