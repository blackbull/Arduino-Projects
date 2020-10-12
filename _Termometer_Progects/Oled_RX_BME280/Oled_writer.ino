

void printSerial() {

  Serial.print("Temperature = ");
  Serial.print(Temp1);
  //Serial.print(bme.readTemperature());
  Serial.println(" *C");

  /*

    Serial.print("Pressure = ");
    //Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
  */
  Serial.print("Hum = ");
  Serial.print(Hum1);
  // Serial.print(bme.readHumidity());
  Serial.println(" %");
  Serial.println();
}

void printOled() {

  myOLED.setFont(BigNumbers);


  //рисуем - или +
  if ( Temp1 < 0) {
    Temp1 = Temp1 * -1;
    myOLED.print(F("-"), 0, 10);
  }
  else {
    myOLED.print(F("+"), 0, 10);
  }

  char t[4];
  dtostrf(  Temp1, 2, 0, t);
  char h[4];
  dtostrf(  Hum1, 2, 0, h);

  myOLED.print(t, 15, 10);
  myOLED.print(h, 15, 40);


  //-------второй градусник-----------


  if (Temp2 > -99 && Hum2 > -99) {


    if ( Temp2 < 0) {
      Temp2 = Temp2 * -1;
      myOLED.print(F("-"), 70, 10);
    }
    else {
      myOLED.print(F("+"), 70, 10);
    }


    dtostrf(  Temp2, 2, 0, t);
    dtostrf(  Hum2, 2, 0, h);

    myOLED.print(t, 85, 10);
    myOLED.print(h, 85, 40);
  }
  else {
    if (NO_Resiver) {
      myOLED.print(F("--"), 85, 10);
      myOLED.print(F("--"), 85, 40);
    }
    else {
      myOLED.print(F(".."), 85, 10);
      myOLED.print(F(".."), 85, 40);
    }
  }



  myOLED.update();


}
