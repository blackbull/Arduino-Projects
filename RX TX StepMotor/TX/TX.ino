#include <VirtualWire.h>

const byte tx_pin = 4;

const byte indicate_pin_tx = 13;

//для таймера
unsigned long nextTime = 0;

void setup()
{
  Serial.begin(9600);
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
    nextTime = millis() + 5000;
    //Serial.println("Start");
    // Serial.println(millis());

    digitalWrite(indicate_pin_tx, HIGH);
    //отправляем синхронизацию
    send ("s");
    delay(100);

    for (byte i = 0; i < 9; i++)
    {
      send ("d");
      delay(10);
    }
    /*
        send ("0");
        delay(10);
        send ("1");
        delay(10);
        send ("2");
        delay(10);
        send ("3");
        delay(10);
        send ("4");
        delay(10);
        send ("5");
        delay(10);
        send ("6");
        delay(10);
        send ("7");
        delay(10);
        send ("8");
        delay(10);
        send ("9");
    */
    digitalWrite(indicate_pin_tx, LOW);

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

