void UpdateTempAndOled() {
//  Temp1 = bme.readTemperature();
 // Hum1 = bme.readHumidity();

Temp1=Temp1-1;
Hum1 =Hum1+1;

if(Temp1>99) Temp1=0;
if(Hum1>99) Hum1=0;

  //декодируем сообщение

 // printSerial();
  printOled();
}
