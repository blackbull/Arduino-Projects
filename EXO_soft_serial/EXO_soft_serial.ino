
#include <SoftwareSerial.h>
SoftwareSerial SIM800(7, 6);        // 8 - RX Arduino (TX SIM800L), 9 - TX Arduino (RX SIM800L)

void setup() {
  Serial.begin(9600);               // Скорость обмена данными с компьютером
  Serial.println("Start!");
  SIM800.begin(9600);               // Скорость обмена данными с модемом
/*
  pinMode(8, OUTPUT); // к DTR пину GSM модуля
  digitalWrite(8, HIGH); // пробуждаем GSM модуль
  digitalWrite(8, LOW); // пробуждаем GSM модуль
  Serial.println("L");
*/
 // SIM800.println("AT");
}

void loop() {

 
  SIM800.println("Send");
  delay(1000);
/*
  if (SIM800.available())           // Ожидаем прихода данных (ответа) от модема...
    Serial.write(SIM800.read());    // ...и выводим их в Serial


  if (Serial.available())           // Ожидаем команды по Serial...
  {
    //char cr=Serial.read();
    SIM800.write(Serial.read());
    //SIM800.write(cr);    // ...и отправляем полученную команду модему
    //Serial.write(cr);
  }*/
  /*
    digitalWrite(8, HIGH);
    Serial.println("H");
    delay(3000);*/
}
