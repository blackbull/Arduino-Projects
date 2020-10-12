#include <VirtualWire.h>
#include <GyverPower.h>
//#include <EEPROM.h>
//#include <Wire.h>
//#include <SPI.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <OLED_I2C.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];

#define PowerPinRX 4
#define PowerPinButton 5
#define ButtonPin 2


#define DEBUG_1_ENABLE
#define DEBUG_2_ENABLE
#define DEBUG_3_ENABLE

#ifdef DEBUG_1_ENABLE
#define DEBUG_ln_1(x) Serial.println(x)
#define DEBUG_1(x) Serial.print(x)
#else
#define DEBUG_ln_1(x)
#define DEBUG_1(x)
#endif

#ifdef DEBUG_2_ENABLE
#define DEBUG_ln_2(x) Serial.println(x)
#define DEBUG_2(x) Serial.print(x)
#else
#define DEBUG_ln_2(x)
#define DEBUG_2(x)
#endif

#ifdef DEBUG_3_ENABLE
#define DEBUG_ln_3(x) Serial.println(x)
#define DEBUG_3(x) Serial.print(x)
#else
#define DEBUG_ln_3(x)
#define DEBUG_3(x)
#endif


//--------------------------------------------инициализация переменных для приема-передачи-------------------------------------------
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;
#define RxPin 3
#define MyMessage_Lenght 10   //длинна моего сообщения s n1 t123 h123 e

String  Message = "";         //переменная для хранения принятой строки
unsigned int count = 0;       //для подсчёта принятого
int Bad = 0;                  //количество бракованных сообщений или пропусков приема



//--------------------------------------------вспомогательные переменные-------------------------------------------

//для таймера
unsigned long nextTime = 0;
unsigned long sleepTime = 0;

//режим работы
byte mode = 0;

//--------------------------------------------Экран-------------------------------------------


OLED myOLED(SDA, SCL); //создаем экземпляр класса OLED с именем myOLED

//-----------------Переменные температуры-------------------

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

float Temp1 = 0;
float Hum1 = 0;

float Temp2 = 0;
float Hum2 = 0;

void VoidFunc() {}
