#include <iarduino_RF433_Receiver.h>                      // Подключаем библиотеку для работы с приёмником MX-RM-5V
#include <GyverPower.h>

iarduino_RF433_Receiver radio(3);                         // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён приёмник (можно подключать только к выводам использующим внешние прерывания)

int                     data[5];                          // Создаём массив для приёма данных

#define PowerPinRX 4
#define PowerPinButton 5


//--------------------------------------------вспомогательные переменные-------------------------------------------

//для таймера
unsigned long nextTime = 0;
unsigned long sleepTime = 0;

//режим работы
byte mode = 0;
bool waitData = false;
int Bad = 0;                  //количество бракованных сообщений или пропусков приема


void setup() {
  Serial.begin(9600);
  //включаем питание приемника
  pinMode(PowerPinRX, OUTPUT);
  digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);
  //включаем питание термометра
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);


  nextTime = millis();
  sleepTime = millis();

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);

  delay(500);

  radio.begin();                                        // Инициируем работу приёмника MX-RM-5V (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
  radio.setDataRate     (i433_1KBPS);                   // Указываем скорость приёма данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
  radio.openReadingPipe (5);                            // Открываем 5 трубу для приема данных (если вызвать функцию без параметра, то будут открыты все трубы сразу, от 0 до 7)
  //  radio.openReadingPipe (2);                            // Открываем 2 трубу для приёма данных (таким образом можно прослушивать сразу несколько труб)
  //  radio.closeReadingPipe(2);                            // Закрываем 2 трубу от  приёма данных (если вызвать функцию без параметра, то будут закрыты все трубы сразу, от 0 до 7)
  radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу
  //  radio.stopListening   ();                             // Выключаем приёмник, если потребуется

  Serial.println(F("================================"));
}



void loop() {

  if (waitData) {

    if (radio.available()) {                              // Если в буфере имеются принятые данные
      radio.read(&data, sizeof(data));                  // Читаем данные в массив data и указываем сколько байт читать

      sleepTime = millis() + 8500; //приняли конечные данные нормально, засыпаем до следующей передачи
      nextTime = sleepTime;
      waitData = false;
      //выводим данные и засыпаем
      mode = 0;

      Serial.print(data[0]);
      Serial.print("  ");
      Serial.print(data[1]);
      Serial.print("  ");
      Serial.print(data[2]);
      Serial.print("  ");
      Serial.print(data[3]);
      Serial.print("  ");
      Serial.println(data[4]);

      //  UpdateTempAndOled();

      //трем сообщение
      data[0] = -500;
      data[1] = -500;
      data[2] = -500;
      data[3] = -500;
      data[4] = -500;


      //отключаем питание
      digitalWrite(PowerPinRX, LOW);

      Serial.println("power Off");
      delay(100);



      //power.sleepDelay(sleepTime - millis());

    }
  }


  if (nextTime <= millis())
  {
    switch (mode)
    {
      case 0:
        {
          Serial.print("Power ON , Bad count= ");
          Serial.println(Bad);
          //включаем питание
          digitalWrite(PowerPinRX, HIGH);

          mode = 1;
          nextTime = millis() + 3000;
          waitData = true;
          break;
        }

      case 1:
        {
          Serial.println("данные не получены  ");

          Bad++;
          //eeprom_update_block((void*)&Bad, 1, sizeof(int));

          nextTime = millis();

          mode = 2;

          // UpdateTempAndOled();
          break;
        }
      case 2:
        {
          //ждем передачи, без отключения питания и сна
          break;
        }
    }
  }


}
