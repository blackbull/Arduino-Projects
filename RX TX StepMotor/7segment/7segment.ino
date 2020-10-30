
const byte indicate_pin_rx = 13;

//--------------------------------------------пины для 7сегментника-------------
const byte a = A0;
const byte b = A1;
const byte c = A2;
const byte d = A3;
const byte e = A4;
const byte f = A5;
const byte g = 6;
const byte dp = 7;

void setup() {

  pinMode(indicate_pin_rx, OUTPUT);
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
  digitalWrite(indicate_pin_rx, HIGH);
  delay(500);
  digitalWrite(indicate_pin_rx, LOW);
}

void loop() {
  /*
    digitalWrite(indicate_pin_rx, HIGH);
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(dp, HIGH);
    delay(500);
    digitalWrite(indicate_pin_rx, LOW);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);

    delay(500);
  */
  /*
    delay(500);
    ShowSimbol('0');
    delay(500);
    ShowSimbol('1');
    delay(500);
    ShowSimbol('2');
    delay(500);
    ShowSimbol('3');
    delay(500);
    ShowSimbol('4');
    delay(500);
    ShowSimbol('5');
    delay(500);
    ShowSimbol('6');
    delay(500);
    ShowSimbol('7');
    delay(500);
    ShowSimbol('8');
    delay(500);
    ShowSimbol('9');
    delay(500);
    ShowSimbol('f');
    delay(500);
    ShowSimbol('e');
    delay(500);
    ShowSimbol('l');
    delay(500);
    ShowSimbol('a');*/
  delay(500);
  ShowByte(1);
  delay(500);
  ShowByte(10);

}

//--------------------------------------------функция отображения для 7сегментника-------------
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


