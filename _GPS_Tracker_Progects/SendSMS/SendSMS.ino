#include <GyverButton.h>

#include <SoftwareSerial.h>
SoftwareSerial Gsm(8, 9);
char phone_no[] = "+79527801280"; //replace with phone no. to get sms

#define PIN 3        // кнопка подключена сюда (PIN --- КНОПКА --- GND)
GButton butt1(PIN);

void setup() {
   Serial.begin(9600);               // Скорость обмена данными с компьютером
  Serial.println("Start!");
  Gsm.begin(9600);               // Скорость обмена данными с модемом
  Gsm.println("AT");

}

void loop() {
  butt1.tick();


String SMS_Text=
  
  if (butt1.isSingle())
  {
    Serial.println("SendSMS");
    SendSMS();
  }
  
if (Gsm.available())           // Ожидаем прихода данных (ответа) от модема...  
    Serial.write(Gsm.read());    // ...и выводим их в Serial

    
  if (Serial.available())           // Ожидаем команды по Serial...
  {
    char cr=Serial.read(); 
    Gsm.write(cr);    // ...и отправляем полученную команду модему
    Serial.write(cr);
  }

}


void SendSMS()
{
  Gsm.print("AT+CMGF=1\r"); //включаем текстовый режим
  delay(400);
  Gsm.print("AT+CMGS=\"");  //начинаем набор текста смс
  Gsm.print(phone_no);      //добавляем номер телефона
  Gsm.println("\"");        //завершаем ввод команды

  delay(300);               //ждем ок

  Gsm.print("TEST SMS TEXT");//набиваем текст смс
  Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26 отправляем символ отправки смс
  delay(200);
}
