#include <VirtualWire.h>
#include <GyverPower.h>

const byte tx_pin = 3;

const byte indicate_pin_tx = 13;

//для таймера
unsigned long nextTime = 0;
int se = 0;


void setup()
{
  Serial.begin(9600);

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);

  pinMode(indicate_pin_tx, OUTPUT);

  vw_set_tx_pin(tx_pin);
  vw_setup(2000);

  digitalWrite(indicate_pin_tx, HIGH);
  delay(500);
  digitalWrite(indicate_pin_tx, LOW);

  nextTime = millis();
  Serial.println("Ready");
}



void loop()
{
  if (nextTime <= millis())
  {
    digitalWrite(9, HIGH);
    digitalWrite(2, HIGH);
    //Serial.println("Start");
    // Serial.println(millis());

    if (se > 99)se = 0;
    else se++;

    Serial.print("Send ");  Serial.println(se);
    digitalWrite(indicate_pin_tx, HIGH);
    //отправляем синхронизацию
    send ("s");
    //delay(100);

    for (byte i = 0; i < 8; i++)
    {
      send ("d");
      //delay(10);
    }

    send ("e");

    digitalWrite(indicate_pin_tx, LOW);

    nextTime = millis() + 10000;

    digitalWrite(9, LOW);
    digitalWrite(2, LOW);

    power.sleepDelay(nextTime - millis() - 300);

    // Serial.println("Stop");
    // Serial.println(millis());
  }

  //send ("1");
}

void send(char *mes)
{
  vw_send((uint8_t *)mes, strlen(mes));
  vw_wait_tx();
}
