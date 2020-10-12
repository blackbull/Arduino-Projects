
#include <SoftwareSerial.h>
#include "GyverTimer.h"


#define RelePin 2
SoftwareSerial SoftSer(12, 11);        // 8 - RX Arduino (TX SIM800L), 9 - TX Arduino (RX SIM800L)

#define OffTime 2000
GTimer OffTimer(MS);

void setup() {
  Serial.begin(9600);               // Скорость обмена данными с компьютером
  SoftSer.begin(9600);               // Скорость обмена данными с модемом

  pinMode(13, OUTPUT); // Светодиод на плате
  pinMode(RelePin, OUTPUT); // пин управления
  digitalWrite(RelePin, HIGH);;

  //analogWrite(A7, 250);
  Serial.println("Start!");
}

void loop() {

  if (OffTimer.isReady()) { //если таймер отключения сработал - отключаем сигнал
    OFF();
  }

  if (SoftSer.available())           // Ожидаем прихода данных (ответа) от модема...
    Serial.write(SoftSer.read());    // ...и выводим их в Serial


  if (Serial.available())           // Ожидаем команды по Serial...
  {
    char cr = Serial.read();

    if (cr != 'H' && cr != 'L' && cr != 'T') {

      SoftSer.write(cr);    // ...и отправляем полученную команду модему
    }
    else  if (cr == 'H') {
      ON();
    }
    else  if (cr == 'L') {
      OFF();
    }
    else  if (cr == 'T') {
      ON();

      OffTimer.setTimeout(OffTime); //ставим таймер автоотключения
    }
  }
}


void ON() {
  digitalWrite(13, HIGH);
  digitalWrite(RelePin, LOW);
}

void OFF() {
  digitalWrite(13, LOW);
  digitalWrite(RelePin, HIGH);
}
