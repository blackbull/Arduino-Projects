void loop() {


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
          count = 0;
          break;
        }
      case 1:
        {
          Serial.println("Символ конца передачи не получен  ");

          Bad++;
          //eeprom_update_block((void*)&Bad, 1, sizeof(int));

          nextTime = millis();

          count = 0;
          Message = "";
          mode = 2;

          UpdateTempAndOled();
          break;
        }

      case 2:
        {
          //ждем передачи, без отключения питания и сна
          break;
        }
      case 3:
        {
          //выводим данные и засыпаем
          mode = 0;
          Serial.print("индикация: ");
          Serial.println(count);
          Serial.println(Message);

          if (count < MyMessage_Lenght) {
            Serial.println("не полный прием данных");
            Bad++;
          }
          else if (count > MyMessage_Lenght) {
            Serial.println("сообщение избыточное");
            Bad++;
          }
          else if (count = MyMessage_Lenght) {
            Serial.println("сообщение полное, обрабатываем");
          }

        //  UpdateTempAndOled();

          //отключаем питание
          digitalWrite(PowerPinRX, LOW);

          Serial.println("power Off");
          delay(100);


          nextTime = sleepTime;

          power.sleepDelay(sleepTime - millis());


          count = 0;
          Message = "";

          break;
        }

    }
  }
}
