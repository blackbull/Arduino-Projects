#include <VirtualWire.h>
#include <CustomStepper.h>            // Подключаем библиотеку управления шаговым двигателем. По умолчанию настроена на двигатель 28BYJ-48-5V



CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя


//--------------------------------------------инициализация переменных для приема-передачи-------------------------------------------
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

const byte rx_pin = 2;

const byte indicate_pin_rx = 13;
const byte indicate_pin_tx = 12;

//--------------------------------------------пины для 7сегментника-------------
const byte a = A0;
const byte b = A1;
const byte c = A2;
const byte d = A3;
const byte e = A4;
const byte f = A5;
const byte g = 6;
const byte dp = 7;

//--------------------------------------------вспомогательные переменные-------------------------------------------

//для таймера
unsigned long nextTime = 0;
bool cantmoving = false;
//режим работы
byte mode = 0;
//для подсчёта принятого
unsigned int count = 0;
unsigned int positionNOW = 0;         //текущая позиция для двигателя

//--------------------------------------------инициализация-------------------------------------------
void setup()
{
  Serial.begin(9600);

  stepper.setRPM(120);                 // Устанавливаем кол-во оборотов в минуту
  stepper.setSPR(400);                // Устанавливаем кол-во шагов на полный оборот. Максимальное значение 4075.7728395

  attachInterrupt(0, getSignal, CHANGE);      //прием на прерываниях

  pinMode(indicate_pin_rx, OUTPUT);
  pinMode(indicate_pin_tx, OUTPUT);

  vw_set_rx_pin(rx_pin);

  vw_setup(2000);
  vw_rx_start();

  //--------------------------------------------инициализация пинов для 7сегментника-------------
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  ShowSimbol(' ');

  //индикация включения
  digitalWrite(indicate_pin_tx, HIGH);
  digitalWrite(indicate_pin_rx, HIGH);
  delay(500);
  digitalWrite(indicate_pin_tx, LOW);
  digitalWrite(indicate_pin_rx, LOW);

  Serial.println("Ready");

  nextTime = millis();
}


//--------------------------------------------основной цикл-------------------------------------------

void loop()
{
  stepper.run();      //команда работы двигателя


  if (nextTime <= millis() || cantmoving)
  {
    if (!cantmoving)
      nextTime = millis() + 1000;

    switch (mode)
    {
      case 0:
        {
          Serial.println("ждём 1");
          ShowSimbol(',');
          mode = 1;
          break;
        }
      case 1:
        {
          Serial.println("ждём 2");
          ShowSimbol(',');
          mode = 2;
          break;
        }
      case 2:
        {
          if (ShowCount(count))
          {
            Serial.print("индикация: ");
            Serial.println(count);
            ShowByte(count);
            count = 0;
            mode = 3;
          }
          else
            cantmoving = true;
          break;
        }
      case 3:
        {
          Serial.println("ожидание");
          mode = 4;
          break;
        }
      case 4:
        {
          if (MoveToPosition(0))
          {
            Serial.println("возврат");
            mode = 0;
          }
          else
            cantmoving = true;
          break;
        }
    }


  }
}

//--------------------------------------------Функция приема данных-------------------------------------------

void getSignal()
{
  if (vw_get_message(message, &messageLength))
  {
    digitalWrite(indicate_pin_rx, true);

    for (int i = 0; i < messageLength; i++)
    {
      char c = message[i];

      Serial.println(c);

      if (c == 's')
      {
        //вызываем синхронизацию
        nextTime = millis() + 1000;
        count = 1;
        mode = 1;
        Serial.println("синхронизация");
      }
      else if (c == 'd')
      {
        count++;
      }
    }
  }

  digitalWrite(indicate_pin_rx, false);
}


//--------------------------------------------Функции работы с двигателем-------------------------------------------

//переместится в позицию по градусам
bool MoveToPosition(unsigned int NEW)
{
  bool ret = false;

  if (stepper.isDone())
  {
    if (positionNOW < NEW)
    {
      stepper.setDirection(CW);
      stepper.rotateDegrees(NEW - positionNOW);
    }
    else
    {
      stepper.setDirection(CCW);
      stepper.rotateDegrees(positionNOW - NEW);
    }

    positionNOW = NEW;

    ret = true;
  }

  return ret;
}

bool ShowCount(byte count)
{
  return MoveToPosition(90 + (count * 20));
}

//--------------------------------------------функции отображения для 7сегментника-------------
void ShowByte(byte s)
{
  switch (s)
  {
    case 0:
      {
        ShowSimbol('0');
        break;
      }
    case 1:
      {
        ShowSimbol('1');
        break;
      }
    case 2:
      {
        ShowSimbol('2');
        break;
      }
    case 3:
      {
        ShowSimbol('3');
        break;
      }
    case 4:
      {
        ShowSimbol('4');
        break;
      }
    case 5:
      {
        ShowSimbol('5');
        break;
      }
    case 6:
      {
        ShowSimbol('6');
        break;
      }
    case 7:
      {
        ShowSimbol('7');
        break;
      }
    case 8:
      {
        ShowSimbol('8');
        break;
      }
    case 9:
      {
        ShowSimbol('9');
        break;
      }
    case 10:
      {
        ShowSimbol('f');
        break;
      }
    default:
      {
        ShowSimbol(' ');
        break;
      }
  }
}

void ShowSimbol(char s)
{
  switch (s)
  {
    case '0':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
    case '1':
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
    case '2':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '3':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '4':
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '5':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '6':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '7':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
    case '8':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case '9':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case 'f':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case 'e':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case 'a':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(dp, HIGH);
        break;
      }
    case 'c':
      {
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
    case 'l':
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
    case ',':
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(dp, LOW);
        break;
      }
    case '.':
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(dp, LOW);
        break;
      }

    default:
      {
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(dp, HIGH);
        break;
      }
  }
}




