#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "GyverTimer.h"
//==============================================================
//#define FistInitial //раздефанить для забивки EEPROM дефолтными значениями
//#define TestFunctions //использовать тестовые функции
// раздефайнить или задефайнить для использования функций вывода в консоль
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

//==============================================================
#define PhonesAdress 0 //0-39
#define OptionsStructAdress 40 //40-47
#define LastWritingStructAdress 48 //48-68
#define GPSstartAdress 72 //72-1024
//==============================================================
TinyGPSPlus gps;
SoftwareSerial GPS_Port(5, 4);
//==============================================================

float  last_Add_LAT, last_Add_LNG, Fresh_LAT, Fresh_LNG;               // переменные расстояния
TinyGPSDate Fresh_date;
TinyGPSTime Fresh_time;
int Fresh_Speed;
bool FreshGPSData = false;    //свежие данные с GPS получены и обработаны

//60000 = 1мин
#define OldGPSDataTime 60000 * 10 
#define GPSReadTime 1000  //время чтения данных c GPS
GTimer GPSReadTimer(MS);
GTimer GPSFreshTimer(MS); //таймер для подсчета насколько свежие GPS данные получены
//==============================================================

struct OptionsStruct { //стартовый адрес 40-47
  byte SleepMode = 0;

  byte LastWritingOPT_Adres = LastWritingStructAdress;
  long MaxWriteCount = 1000000;
  byte FistLoad = 200;
};

struct LastWritingStruct {//стартовый адрес 48-68
  int LastAdress = GPSstartAdress; //для хранения координат в структуре 69-1024
  long WriteCount = 0;
};

struct GpsDataStruct {//стартовый адрес 69-1024
  float LAT = 0;
  float LNG = 0;

  byte Speed = 0;
  byte Month = 0;
  byte Day = 0;

  byte Hour = 0;
  byte Min = 0;
  byte Sec = 0;

  byte StatusCode = 0;
};

String Phones = "111111111111_222222222222_333333333333"; // админские телефоны стартовый адрес 0
OptionsStruct OptionsSTR; //переменная для основных хранимых опций
LastWritingStruct LastWritingSTR; //переменная для хранения ссылок на посленюю сохраненную координату в памяти
GpsDataStruct GPSData; //переменная для загрузки последней сохраненной координаты


void voidFunc() {} //если в главном файле нет никаких функций, то происходит какой то глюк компиляции, из-за которого в других вкладках не видно структур
