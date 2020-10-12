void UpdateTempAndOled() {

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

   Temp1 = temp.temperature;
   Hum1 = humidity.relative_humidity;



  Serial.print(Temp1); 
  Serial.println(" *C");

  Serial.print(Hum1);
  Serial.println(" %");


  //  Temp1 = bme.readTemperature();
  // Hum1 = bme.readHumidity();

/*
  if (Temp1 > 99) Temp1 = 0;
  if (Hum1 > 99) Hum1 = 0;
*/
  //декодируем сообщение




 //  printSerial();
  printOled();
}
