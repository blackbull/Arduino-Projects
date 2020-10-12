#include <Adafruit_AHTX0.h>
//#include <Adafruit_BME280.h>

Adafruit_AHTX0 aht;

//Adafruit_BME280 bme;

#define PowerPinRX 4
#define PowerPinButton 5
#define ButtonPin 2

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  //включаем питание приемника
  pinMode(PowerPinRX, OUTPUT);
  digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);
  //включаем питание термометра
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  
  delay(1000);




  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
/*
  if (! bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }*/
}

void loop() {

  for (int i = 0; i < 5; i++) {

    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    Serial.print(F("T ")); Serial.print(temp.temperature);
    Serial.print(" H "); Serial.print(humidity.relative_humidity); Serial.println("%");
   // Serial.println();
/*
    Serial.print("T "); Serial.print(bme.readTemperature());
    Serial.print(" H ");  Serial.print(bme.readHumidity());  Serial.print("%");
    Serial.print(" P "); Serial.print(bme.readPressure() / 100.0F); Serial.println(" hPa");*/
    delay(100);


  }

  
 
  delay(5000);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  Serial.println("on");





}
