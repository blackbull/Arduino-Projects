


#include <SoftwareSerial.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include "GyverButton.h"

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


int pin = 2; // подключается к ring пину gsm модуля
byte stat = 0;
SoftwareSerial SIM800(7, 6);                                  // RX, TX
bool InitialGSMFlag = false;

bool ButFlag1 = false;
bool ButFlag2 = false;

GButton butt1(12);
GButton butt2(11);

void setup() {
  //set_sleep_mode(SLEEP_MODE_STANDBY); //Определяем режим сна
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW); // 0 для кнопки 2

  pinMode(2, INPUT);//индикация RING
  pinMode(13, OUTPUT);

  pinMode(8, OUTPUT); // к DTR пину GSM модуля
  // digitalWrite(7, LOW); // пробуждаем GSM модуль


  Serial.begin(9600);
  Serial.println("GSM test.");

  SIM800.begin(9600);

  delay(300);

  // InitialGSM();

}

void loop() {
  butt1.tick();
  butt2.tick();

  if (butt1.isSingle()) {
    digitalWrite(8, LOW);
    Serial.println("-----DTR LOW-----");
  }

  if (butt2.isSingle()) {
    digitalWrite(8, HIGH);
    Serial.println("-----DTR HIGH-----");
  }

  digitalWrite(13, digitalRead(2));


  // EnterSleep(); //Пора спать


  if (SIM800.available())           // Ожидаем прихода данных (ответа) от модема...
    Serial.write(SIM800.read());    // ...и выводим их в Serial


  if (Serial.available())           // Ожидаем команды по Serial...
  {
    SIM800.write(Serial.read());
  }

}

void wakeUp()
{
  Serial.println("WakeUp"); //Проснулись
  detachInterrupt(0); //Отключаем прерывания
  digitalWrite(6, LOW); // пробуждаем GSM модуль
  delay(500);
}

void EnterSleep()
{
  attachInterrupt(0, wakeUp, LOW); //Если на 0-вом прерываниии - ноль, то просыпаемся.
  delay(100);

  sleep_enable(); //Разрешаем спящий режим
  sleep_mode(); //Спим (Прерывания продолжают работать.) Программа останавливается.
  sleep_disable(); //Запрещаем спящий режим
}


bool InitialGSM() {
  InitialGSMFlag = false;
  DEBUG_ln_2("InitialGSM -> Start");

  String ans = sendATCommand("AT", true);
  ans.trim();
  if ( ans.endsWith("OK"))      // Отправили AT для настройки скорости обмена данными
  {
    //sendATCommand("AT+CMGDA=\"DEL ALL\"", true);               // Удаляем все SMS, чтобы не забивать память

    // Команды настройки модема при каждом запуске
    sendATCommand("ATE0", true);                                //ывключаем ЭХО
    sendATCommand("AT+CLIP=1", true);                           // Включаем АОН
    //_response = sendATCommand("AT+DDET=1", true);             // Включаем DTMF
    // sendATCommand("AT+CPMS=SM,SM,SM", true);                  //установить память для сохранения смс -> сим карта
    sendATCommand("AT+CNMI=1,0", true);                       //не выводить сообщение о пришедших смс, а сразу сохранять их в сим
    sendATCommand("AT+CMGF=1", true);                        // Включаем текстовый режима SMS (Text mode) и сразу сохраняем значение (AT&W)(не сохраняем, что бы не расходовать ресурс памяти)!
    InitialGSMFlag = true;

    DEBUG_ln_2(F(" InitialGSM -> OK"));
  }
  else DEBUG_ln_1(F(" InitialGSM -> ERROR"));

  return InitialGSMFlag;
}
