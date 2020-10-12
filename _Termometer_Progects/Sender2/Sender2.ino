#include <iarduino_RF433_Transmitter.h>                   // Подключаем библиотеку для работы с передатчиком FS1000A
iarduino_RF433_Transmitter radio(3);                     // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён передатчик
int                        data[5];                       // Создаём массив для передачи данных

#include <GyverPower.h>


//для таймера
unsigned long nextTime = 0;
const byte indicate_pin_tx = 13;

void setup() {

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  radio.begin();                                        // Инициируем работу передатчика FS1000A (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
  radio.setDataRate     (i433_1KBPS);                   // Указываем скорость передачи данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
  radio.openWritingPipe (5);                            // Открываем 5 трубу для передачи данных (передатчик может передавать данные только по одной из труб: 0...7)

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);

  pinMode(indicate_pin_tx, OUTPUT);

  data[0] = -100;
  data[1] = 1;
  data[4] = -200;

  Serial.begin(9600);
  Serial.println("=================================");

  nextTime = millis();

}                                                         // Если повторно вызвать функцию openWritingPipe указав другой номер трубы, то передатчик начнёт передавать данные по вновь указанной трубе

int i = -1000;

void loop() {





  if (nextTime <= millis())
  {
    digitalWrite(9, HIGH);
    digitalWrite(2, HIGH);
    data[2] = i;
    data[3] = i + 1;


    radio.write(&data, sizeof(data));                     // отправляем данные из массива data указывая сколько байт массива мы хотим отправить

    nextTime = millis() + 10000;

    digitalWrite(9, LOW);
    digitalWrite(2, LOW);

    i = i + 1;

    if (i > 100) i = 0;
    // Serial.print("Sending ");
    Serial.println(i);

    delay(200);
    power.sleepDelay(nextTime - millis() - 300);

  }
}
