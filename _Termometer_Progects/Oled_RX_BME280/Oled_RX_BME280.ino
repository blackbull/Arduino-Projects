#include <iarduino_RF433_Receiver.h>                      // Подключаем библиотеку для работы с приёмником MX-RM-5V
#include <GyverPower.h>
#include <Adafruit_BME280.h>
#include <OLED_I2C.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];

#define PowerPinRX 4
#define PowerPinButton 5
#define PowerPinTermometr 6
#define ButtonPin 2

#define UpdateTime 8500



//--------------------------------------------инициализация переменных для приема-передачи-------------------------------------------
iarduino_RF433_Receiver radio(3);                         // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён приёмник (можно подключать только к выводам использующим внешние прерывания)
int                     data[5];                          // Создаём массив для приёма данных

#define RxPin 3


//--------------------------------------------вспомогательные переменные-------------------------------------------

//для таймера
unsigned long nextTime = 0;
unsigned long sleepTimeForNextRX = 0;
unsigned long GlobalwaitResiveTimer = 0;

bool NO_Resiver = false;
bool waitData = false;
int Bad = 0;                  //количество бракованных сообщений или пропусков приема

//режим работы
byte mode = 0;

//--------------------------------------------Экран-------------------------------------------


OLED myOLED(SDA, SCL); //создаем экземпляр класса OLED с именем myOLED

//-----------------Переменные температуры-------------------

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

float Temp1 = -100;
float Hum1 = -100;

float Temp2 = -100;
float Hum2 = -100;

void VoidFunc() {}
