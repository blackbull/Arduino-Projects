// раздефайнить или задефайнить для использования
#define DEBUG_1_ENABLE
//#define DEBUG_2_ENABLE
//#define DEBUG_3_ENABLE

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

// миллис хранится в переменной timer0_millis в файлах ядра
// делаем её extern для возможности прямого изменения
extern volatile unsigned long timer0_millis;

void setup() {

#ifdef DEBUG_1_ENABLE || DEBUG_2_ENABLE|| DEBUG_3_ENABLE
  Serial.begin(9600);
#endif
  // за 5 секунд до переполнения миллис
  timer0_millis = UINT32_MAX - 5000;
}

byte i=0;

uint32_t timer;
void loop() {
  // наш стандартный таймер с секундным периодом
  if (millis() - timer >= 100) {
    timer = millis();

    // выводим миллис в секундах
    DEBUG_1(millis() / 1000L); DEBUG_ln_1("  DEBUG_ln_1");
    DEBUG_2(millis() / 1000L); DEBUG_ln_2("  DEBUG_ln_2");

    DEBUG_ln_1(i);
    i++;
    // наблюдаем как перешёл через переполнение
    // и работает себе спокойно дальше
  }
}
