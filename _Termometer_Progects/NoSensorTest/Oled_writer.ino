

void printSerial() {

  Serial.print("Temperature = ");
  //Serial.print(bme.readTemperature());
  Serial.println(" *C");



  Serial.print("Pressure = ");
  //Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
 // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Hum = ");
 // Serial.print(bme.readHumidity());
  Serial.println(" %");
  Serial.println();
}

void printOled() {

  myOLED.setFont(BigNumbers);

  // Temp1 = Temp1 * -1;


  //рисуем - или +
  if ( Temp1 < 0) {
    Temp1 = Temp1 * -1;
    myOLED.print("-", 0, 10);
  }
  else {
    printPlus(0, 10);
  }
 
    char t[4];
    dtostrf(  Temp1, 2, 0, t);
    char h[4];
    dtostrf(  Hum1, 2, 0, h);

    myOLED.print(t, 15, 10);
    myOLED.print(h, 15, 40);
  
  // myOLED.print(t, 50, 10);
  // myOLED.print(h, 50, 35);

  myOLED.update();


  /*
    oled.clear();
    oled.print(bme.readTemperature());
    oled.println(" *C");
    oled.println("");

    oled.print(bme.readHumidity());
    oled.println(" %");*/
}


void printPlus(byte x, byte y) {

  myOLED.setPixel(x + 2, y + 12);//старт слева
  myOLED.setPixel(x + 3, y + 12);
  myOLED.setPixel(x + 4, y + 12);
  myOLED.setPixel(x + 5, y + 12);
  myOLED.setPixel(x + 6, y + 12);
  myOLED.setPixel(x + 7, y + 12);
  myOLED.setPixel(x + 8, y + 12);
  myOLED.setPixel(x + 9, y + 12);
  myOLED.setPixel(x + 10, y + 12);
  myOLED.setPixel(x + 11, y + 12);

  myOLED.setPixel(x + 3, y + 11);
  myOLED.setPixel(x + 4, y + 11);
  myOLED.setPixel(x + 5, y + 11);
  myOLED.setPixel(x + 6, y + 11);
  myOLED.setPixel(x + 7, y + 11);
  myOLED.setPixel(x + 8, y + 11);
  myOLED.setPixel(x + 9, y + 11);
  myOLED.setPixel(x + 10, y + 11);

  myOLED.setPixel(x + 3, y + 13);
  myOLED.setPixel(x + 4, y + 13);
  myOLED.setPixel(x + 5, y + 13);
  myOLED.setPixel(x + 6, y + 13);
  myOLED.setPixel(x + 7, y + 13);
  myOLED.setPixel(x + 8, y + 13);
  myOLED.setPixel(x + 9, y + 13);
  myOLED.setPixel(x + 10, y + 13);

  myOLED.setPixel(x + 6, y + 8);
  myOLED.setPixel(x + 7, y + 8);
  myOLED.setPixel(x + 6, y + 9);
  myOLED.setPixel(x + 7, y + 9);
  myOLED.setPixel(x + 6, y + 10);
  myOLED.setPixel(x + 7, y + 10);
  myOLED.setPixel(x + 6, y + 14);
  myOLED.setPixel(x + 7, y + 14);
  myOLED.setPixel(x + 6, y + 15);
  myOLED.setPixel(x + 7, y + 15);
  myOLED.setPixel(x + 6, y + 16);
  myOLED.setPixel(x + 7, y + 16);

  myOLED.setPixel(x + 7, y + 7);
  myOLED.setPixel(x + 6, y + 17);
}
