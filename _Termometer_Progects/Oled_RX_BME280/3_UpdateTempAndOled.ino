void UpdateTempAndOled() {

  Temp1 = bme.readTemperature();
  Hum1 = bme.readHumidity();


  Serial.print(Temp1);
  Serial.print(" *C  ");

  Serial.print(Hum1);
  Serial.println(" %");


  /*
    if (Temp1 > 99) Temp1 = 0;
    if (Hum1 > 99) Hum1 = 0;
  */
  //декодируем сообщение




  //  printSerial();
  printOled();
}
