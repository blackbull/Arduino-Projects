
#include <CustomStepper.h>            // Подключаем библиотеку управления шаговым двигателем. По умолчанию настроена на двигатель 28BYJ-48-5V
CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя

byte mode = 0;                        //режим работы
unsigned int positionNOW = 0;         //текущая позиция


void setup()
{
  stepper.setRPM(200);                 // Устанавливаем кол-во оборотов в минуту
  stepper.setSPR(400);                // Устанавливаем кол-во шагов на полный оборот. Максимальное значение 4075.7728395



  //индикация включения
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}




//переместится в позицию по градусам
void MoveToPosition(unsigned int NEW)
{
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
  }
}

void ShowCount(byte count)
{
  MoveToPosition(90 + (count * 20));
}




void loop()
{
  stepper.run();

  switch (mode)
  {
    case 0:
      {
        ShowCount(5);
        mode = 1;
        break;
      }

    case 1:
      {
        if (stepper.isDone())
        {
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
          MoveToPosition(0);
        }
        break;
      }

      case 2:
      {

        break;
      }

  }







  /*
    if (stepper.isDone() && positionNOW < 360)
    {
      delay(100);
      stepper.setDirection(CCW);
      stepper.rotateDegrees(1);
      positionNOW += 1;
    }

  */


  /*
    if (stepper.isDone() and example == 1)
    {
      if (ccw)
      {
        stepper.setDirection(CCW);
      }
      else
      {
        stepper.setDirection(CW);
      }
      stepper.rotate(1);
      stepper.rotateDegrees(90);

      example = 2;
    }



    if (stepper.isDone() and example == 2)
    {
      delay(3000);
      example = 1;

      ccw = !ccw;
    }
  */

  /*
    if (stepper.isDone() and example == 1)  // Когда предыдущая команда выполнена (см. ниже), метод stepper.isDone() возвращает true
    {
    stepper.setDirection(CW);         // Устанавливает направление вращения. Может принимать 3 значения: CW - по часовой, CCW - против часовой, STOP
    stepper.rotate(1);                // Устанавливает вращение на заданное кол-во оборотов
    example = 2;
    }
    if (stepper.isDone() and example == 2)
    {
    stepper.setDirection(CCW);
    stepper.rotateDegrees(90);        // Поворачивает вал на заданное кол-во градусов. Можно указывать десятичную точность (например 90.5), но не принимаются отрицательные значения
    example = 3;
    }
    if (stepper.isDone() and example == 3)
    {
    stepper.setDirection(CW);
    stepper.rotate();                 // Будет вращать пока не получит команду о смене направления или пока не получит директиву STOP

    example = 1;
    }
    stepper.run();                      // Этот метод обязателен в блоке loop. Он инициирует работу двигателя, когда это необходимо

  */
}
