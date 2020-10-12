void loop() {


  if (waitData) {

    if (!NO_Resiver && radio.available()) {                             // Если в буфере имеются принятые данные
      radio.read(&data, sizeof(data));                  // Читаем данные в массив data и указываем сколько байт читать

      sleepTimeForNextRX = millis() + UpdateTime; //приняли конечные данные нормально, засыпаем до следующей передачи
      nextTime = sleepTimeForNextRX;
      waitData = false;
      //выводим данные и засыпаем
      mode = 0;

      Serial.print(data[0]);
      Serial.print("  ");
      Serial.print(data[1]);
      Serial.print("  ");
      Serial.print(data[2]);
      Serial.print("  ");
      Serial.print(data[3]);
      Serial.print("  ");
      Serial.println(data[4]);

      UpdateTempAndOled();

      //трем сообщение
      data[0] = -500;
      data[1] = -500;
      data[2] = -500;
      data[3] = -500;
      data[4] = -500;


      //отключаем питание
      digitalWrite(PowerPinRX, LOW);

      Serial.println(F("power Off"));
      delay(100);



      //power.sleepDelay(sleepTimeForNextRX - millis());

    }
    else {
      UpdateTempAndOled();
      if (GlobalwaitResiveTimer <= millis()) {
        //отключаем питание
        digitalWrite(PowerPinRX, LOW);
        NO_Resiver = true;
        Serial.println(F("no_Resiver"));
        delay(200);
        power.sleepDelay(UpdateTime);
      }
    }
  }


  if (nextTime <= millis())
  {
    switch (mode)
    {
      case 0:
        {
          Serial.print("Power ON , Bad count= ");
          Serial.println(Bad);
          //включаем питание
          digitalWrite(PowerPinRX, HIGH);

          mode = 1;
          nextTime = millis() + 3000;
          waitData = true;
          break;
        }

      case 1:
        {
          Serial.println("данные не получены  ");

          Bad++;
          //eeprom_update_block((void*)&Bad, 1, sizeof(int));

          nextTime = millis();

          mode = 2;

          // UpdateTempAndOled();
          break;
        }
      case 2:
        {
          //ждем передачи, без отключения питания и сна
          break;
        }
    }
  }


}
