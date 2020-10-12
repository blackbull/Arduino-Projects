#include <EEPROM.h>

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

#define PhonesAdress 0 //0-39
String Phones = "44444444444444444";
//String Phones = "111111111111_222222222222_333333333333";


void voidFunc() {} //если в главном файле нет никаких функций, то происходит какой то глюк компиляции, из-за которого в других вкладках не видно структур
