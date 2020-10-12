void loop() {
  bme.takeForcedMeasurement(); // has no effect in normal mode

  Temp1 = bme.readTemperature();
  Hum1 = bme.readHumidity();

  printSerial();
  printOled();

  delay(delayTime);
}
