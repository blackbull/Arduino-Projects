#include <VirtualWire.h>
#include <GyverPower.h>
#include <EEPROM.h>

#define PowerPinRX 4
#define PowerPinButton 5
#define ButtonPin 2


#define DEBUG_1_ENABLE
#define DEBUG_2_ENABLE
#define DEBUG_3_ENABLE

#ifdef DEBUG_1_ENABLE
#define DEBUG_ln_1(x) Serial.println(x)
#define DEBUG_1(x) Serial.print(x)
#else
#define DEBUG_ln_1(x)
#define DEBUG_1(x)
#endif

#ifdef DEBUG_2_ENABLE
#define DEBUG_ln_2(x) Serial.println(x)
#define DEBUG_2(x) Serial.print(x)
#else
#define DEBUG_ln_2(x)
#define DEBUG_2(x)
#endif

#ifdef DEBUG_3_ENABLE
#define DEBUG_ln_3(x) Serial.println(x)
#define DEBUG_3(x) Serial.print(x)
#else
#define DEBUG_ln_3(x)
#define DEBUG_3(x)
#endif


//--------------------------------------------инициализация переменных для приема-передачи-------------------------------------------
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

const byte rx_pin = 3;

#define MyMessage_Lenght 10   //длинна моего сообщения s n1 t123 h123 e

String  Message = "";         //переменная для хранения принятой строки
unsigned int count = 0;       //для подсчёта принятого
int Bad = 0;                  //количество бракованных сообщений или пропусков приема

//--------------------------------------------вспомогательные переменные-------------------------------------------

//для таймера
unsigned long nextTime = 0;
unsigned long sleepTime = 0;

//режим работы
byte mode = 0;
bool SinhrOK = false;



//--------------------------------------------инициализация-------------------------------------------
void setup()
{
  Serial.begin(9600);

  //включаем питание приемника
  pinMode(PowerPinRX, OUTPUT);
  digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);

  //настройка приемника
  vw_set_rx_pin(rx_pin);
  vw_setup(2000);
  vw_rx_start();
  attachInterrupt(1, getSignal, CHANGE);      //прием на прерываниях


  nextTime = millis();
  sleepTime = millis();

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP);

  //eeprom_update_block((void*)&Bad, 1, sizeof(int));

  eeprom_read_block((void*)&Bad, 1, sizeof(int));


  Serial.println("Ready");


}


//--------------------------------------------основной цикл-------------------------------------------

void loop()
{
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
          count = 0;
          break;
        }
      case 1:
        {
          Serial.println("Символ конца передачи не получен  ");

          Bad++;
          eeprom_update_block((void*)&Bad, 1, sizeof(int));

          nextTime = millis();

          count = 0;
          Message = "";
          mode = 2;
          break;
        }

      case 2:
        {
          //ждем передачи, без отключения питания и сна
          break;
        }
      case 3:
        {
          //выводим данные и засыпаем
          mode = 0;
          Serial.print("индикация: ");
          Serial.println(count);
          Serial.println(Message);

          if (count < MyMessage_Lenght) {
            Serial.println("не полный прием данных");
            Bad++;
          }
          else if (count > MyMessage_Lenght) {
            Serial.println("сообщение избыточное");
            Bad++;
          }
          else if (count = MyMessage_Lenght) {
            Serial.println("сообщение полное, обрабатываем");
          }



          //отключаем питание
          digitalWrite(PowerPinRX, LOW);
          
          Serial.println("power Off");
          delay(100);

        //  digitalWrite(13, HIGH);
          nextTime = sleepTime;

          power.sleepDelay(sleepTime - millis());

        //  digitalWrite(13, LOW);


          count = 0;
          Message = "";

          break;
        }

    }


  }
}

//--------------------------------------------Функция приема данных-------------------------------------------

void getSignal()
{
  //данные приходят по одному байту, поэтому обработка на прерываниях

  if (vw_get_message(message, &messageLength))
  {
    for (int i = 0; i < messageLength; i++)
    {
      char c = message[i];
      Message += c;
      Serial.println(c);

      if (c == 's') //символ начала передачи
      {
        //начало передачи
        nextTime = millis() + 2000; //подправляем время окончания передачи
        count = 1;
      }

      else if (c == 'd')
      {
        count++;
      }
      else if (c == 'e') //символ окончания передачи
      {
        sleepTime = millis() + 8500; //приняли конечные данные нормально, засыпаем до следующей передачи

        mode = 3;
        count++;
      }
    }
  }
}
