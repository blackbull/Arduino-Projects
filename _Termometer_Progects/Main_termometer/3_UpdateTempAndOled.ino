void UpdateTempAndOled() {
  Temp1 = bme.readTemperature();
  Hum1 = bme.readHumidity();

  //декодируем сообщение

 // printSerial();
  printOled();
}
