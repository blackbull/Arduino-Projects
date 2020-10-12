#include <iarduino_RF433_Receiver.h>                      // Подключаем библиотеку для работы с приёмником MX-RM-5V
#include <GyverPower.h>
#include <Adafruit_AHTX0.h>
#include <OLED_I2C.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];

#define PowerPinRX 4
#define PowerPinButton 5
#define ButtonPin 2



//--------------------------------------------инициализация переменных для приема-передачи-------------------------------------------
iarduino_RF433_Receiver radio(3);                         // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён приёмник (можно подключать только к выводам использующим внешние прерывания)
int                     data[5];                          // Создаём массив для приёма данных

#define RxPin 3
bool waitData = false;
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

Adafruit_AHTX0 aht;

float Temp1 = 11;
float Hum1 = 15;

float Temp2 = 0;
float Hum2 = 0;

void VoidFunc() {}
