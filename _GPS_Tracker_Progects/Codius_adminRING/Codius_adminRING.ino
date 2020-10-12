// раздефайнить или задефайнить для использования
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



#include <SoftwareSerial.h>                                   // Библиотека програмной реализации обмена по UART-протоколу
SoftwareSerial SIM800(7, 6);                                  // RX, TX

int pins[3] = {4, 5, 6};                                      // Пины с подключенными светодиодами

String _response    = "";                                     // Переменная для хранения ответа модуля
long lastUpdate = millis();                                   // Время последнего обновления
long updatePeriod   = 30000;                                  // Проверять каждую минуту
bool InitialGSMFlag = false;
String phones = "111111111111_222222222222_333333333333";   // Белый список телефонов


struct MyStruct { //структура хранения опций
    byte FistLoad; //если будет считываться 200, то все норм, если другое значение значит это первый запуск, надо установить дефолтные значения и сохранть а ROM
    int b;
    float c;
};
