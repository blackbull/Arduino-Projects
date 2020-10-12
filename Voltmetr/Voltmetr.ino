
#define pinVcc A0
#define pinBat A1
#define R1 4660.0  //к Vcc  в омах
#define R2 2150.0  //к GND  в омах
#define RealVcc_arduino 5.1 //реальное напряжение питания ардуино на пине +5В

#include <SoftwareSerial.h>
#include "GyverTimer.h"

#define Low_Bat_Level 3 //3 вольта
#define Low_Acc_Level 8
#define StartEngine_Acc_Level 11

#define VoltmeterReadTime 1000 //10 сек
GTimer VoltmeterReadTimer(MS, VoltmeterReadTime); //таймер для проверки пришедших СМС

//bool EngineStarted = false;
//bool Low_Bat = false;
bool Low_Acc_Warning_Send = true;
byte AccLevelCounter = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

  Serial.println(F("==============================================="));
}

void loop() {

  if (VoltmeterReadTimer.isReady()) { // проверяем напряжение

    float Vcc = GetVccVolt();
    Serial.print(Vcc); Serial.print("  ");
    Serial.println(AccLevelCounter);

    if (Vcc > Low_Acc_Level && Vcc < StartEngine_Acc_Level) { //если напряжение в норме, сбрасываем счетчик
      AccLevelCounter = 100;
    }


    if (Vcc < Low_Acc_Level) {//считаем время низкого уровня входящего питания

      if (AccLevelCounter > 100) {//если двигатель был ранее заведен - сбрасываем счетчик
        AccLevelCounter = 100;
      }

      if (AccLevelCounter == 100 - 12) {//низкий уровень длится уже 2 минуты -> шлем смс с предупреждением

        if (!Low_Acc_Warning_Send) { // если ранее не отправлялось смс
          Low_Acc_Warning_Send = true;
          //Отправляем СМС
          Serial.println("SMS ACC LOW Level ");
        }
      }
      if (AccLevelCounter > 20) { //защита от переполнения
        AccLevelCounter--;
      }
    }



    if (Vcc > StartEngine_Acc_Level) {//считаем время уровня входящего питания заведенного двигателя

      if (AccLevelCounter < 100) {//если заряд аккомулятора был низкий - сбрасываем счетчик
        AccLevelCounter = 100;
      }

      if (AccLevelCounter == 100 + 6) {//высокий уровень длится уже 1 минуты -> двигатель заведен

        Serial.println("Engine Started");
      }

      if (AccLevelCounter == 100 + 48) {//высокий уровень длится уже 8 минуты -> можно "перезарядить" отправку смс о низком заряде аккомулятора
        Low_Acc_Warning_Send = false;
        Serial.println("Low_Acc_Warning_Send = false;");
      }

      if (AccLevelCounter < 240) {//защита от переполнения
        AccLevelCounter++;
      }
    }









  }

  /*
    int  valA1 = analogRead(pinBat);
    float  voutA1 = (valA1 * RealVcc_arduino) / 1024.0;

    int  valA0 = analogRead(pinVcc);
    float  voutA0 = (valA0 * RealVcc_arduino) / 1024.0;
    float coef = (R2 / (R1 + R2));
    float voutA00 = voutA0 / coef;


    Serial.print("Bat: "); Serial.print(voutA1); Serial.print(" Vcc: "); Serial.print(voutA0);
    Serial.print(" coef: ");  Serial.print(coef); Serial.print(" VccC: "); Serial.println(voutA00);*/
}

float GetBatVolt() {
  return (analogRead(pinBat) * RealVcc_arduino) / 1024.0;
}

float GetVccVolt() {
  return ((analogRead(pinVcc) * RealVcc_arduino) / 1024.0) / (R2 / (R1 + R2));
}
