#include <OLED_I2C.h>
#include <GyverPower.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];

OLED myOLED(SDA, SCL); //создаем экземпляр класса OLED с именем myOLED

#include "GyverEncoder.h"
#define BTN_PIN 10   // пин кнопки
#define CLK 8              // s1 энкодера
#define DT 9               // s2 энкодера


Encoder enc1(CLK, DT, BTN_PIN);

uint8_t mode = 0;
uint8_t britnes = 0;
bool demo = 0;

void setup() {

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  delay(1000);

  // put your setup code here, to run once:
  myOLED.begin(); //инициализируем дисплей
  myOLED.clrScr();                                          //Очищаем буфер дисплея.
  myOLED.setFont(SmallFont);                                //Перед выводом текста необходимо выбрать шрифт

  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 0);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 10);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 20);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 30);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 40);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 50);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 60);


  myOLED.update();
  //myOLED.setFont(BigNumbers);

  enc1.setTickMode(AUTO);
  enc1.setType(TYPE2);
  enc1.setDirection(REVERSE);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  delay(2000);
  myOLED.clrScr();
  myOLED.update();
  digitalWrite(13, LOW);

  delay(2000);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 0);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 10);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 20);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 30);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 40);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 50);
  myOLED.print(F("MODEDEMOBRIGHTMODEDEMOBRIGHT"), 0, 60);


  myOLED.update();

  power.sleepDelay(10000);
}

void loop() {
  if (enc1.isRight()) {
    mode++;

    char sd[3];
    sprintf(sd, "%02d", mode);
    myOLED.print(sd, 0, 15);
    myOLED.update();

    demo = !demo;
    char sd2[3];
    sprintf(sd2, "%01d", demo);
    myOLED.print(sd2, 55, 40);
    myOLED.update();
  };


  if (enc1.isLeft()) {
    mode--;

    char sd[3];
    sprintf(sd, "%02d", mode);
    myOLED.print(sd, 0, 15);
    myOLED.update();

    demo = !demo;

    char sd2[3];
    sprintf(sd2, "%01d", demo);
    myOLED.print(sd2, 55, 40);
    myOLED.update();
  };

  if (enc1.isRightH()) {
    britnes++;

    char sd[3];
    sprintf(sd, "%03d", britnes);
    myOLED.print(sd, 87, 15);
    myOLED.update();
  }

  if (enc1.isLeftH()) {
    britnes--;

    char sd[3];
    sprintf(sd, "%03d", britnes);
    myOLED.print(sd, 87, 15);
    myOLED.update();
  }
}
