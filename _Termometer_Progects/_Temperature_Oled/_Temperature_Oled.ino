#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <OLED_I2C.h>
extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];
OLED myOLED(SDA, SCL); //создаем экземпляр класса OLED с именем myOLED

#define SEALEVELPRESSURE_HPA (1013.25)


Adafruit_BME280 bme; // I2C

unsigned long delayTime;

float Temp1=0;
float Hum1=0;

float Temp2=0;
float Hum2=0;
