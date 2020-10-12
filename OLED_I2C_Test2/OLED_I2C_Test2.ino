#include <OLED_I2C.h>

#define PowerPinRX 4
#define PowerPinButton 5
#define PowerPinTermometr 6
#define ButtonPin 2


extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];



OLED myOLED(SDA, SCL); //создаем экземпляр класса OLED с именем myOLED




void setup() {
  Serial.begin(9600);


  pinMode(PowerPinRX, OUTPUT);
  digitalWrite(PowerPinRX, HIGH);
  //включаем питание кнопки
  pinMode(PowerPinButton, OUTPUT);
  digitalWrite(PowerPinButton, HIGH);
  //включаем питание термометра
  pinMode(PowerPinTermometr, OUTPUT);
  digitalWrite(PowerPinTermometr, HIGH);


  delay(100);

  // put your setup code here, to run once:
  myOLED.begin(); //инициализируем дисплей
  myOLED.clrScr();                                          //Очищаем буфер дисплея.
  myOLED.setFont(BigNumbers);

  myOLED.print(F("+-/!9"), 0, 0);
  printPlus(0, 30);
  printPlus(15, 30);
 // myOLED.print(F("   "), 0, 30);
  
  // myOLED.print(F("67890/:+"), 0, 30);
  myOLED.update();

  Serial.println(F("=============================="));
}

void loop() {

}


void printPlus(byte x, byte y) {

  myOLED.setPixel(x + 2, y + 12);//старт слева
  myOLED.setPixel(x + 3, y + 12);
  myOLED.setPixel(x + 4, y + 12);
  myOLED.setPixel(x + 5, y + 12);
  myOLED.setPixel(x + 6, y + 12);
  myOLED.setPixel(x + 7, y + 12);
  myOLED.setPixel(x + 8, y + 12);
  myOLED.setPixel(x + 9, y + 12);
  myOLED.setPixel(x + 10, y + 12);
  myOLED.setPixel(x + 11, y + 12);

  myOLED.setPixel(x + 3, y + 11);
  myOLED.setPixel(x + 4, y + 11);
  myOLED.setPixel(x + 5, y + 11);
  myOLED.setPixel(x + 6, y + 11);
  myOLED.setPixel(x + 7, y + 11);
  myOLED.setPixel(x + 8, y + 11);
  myOLED.setPixel(x + 9, y + 11);
  myOLED.setPixel(x + 10, y + 11);

  myOLED.setPixel(x + 3, y + 13);
  myOLED.setPixel(x + 4, y + 13);
  myOLED.setPixel(x + 5, y + 13);
  myOLED.setPixel(x + 6, y + 13);
  myOLED.setPixel(x + 7, y + 13);
  myOLED.setPixel(x + 8, y + 13);
  myOLED.setPixel(x + 9, y + 13);
  myOLED.setPixel(x + 10, y + 13);

  myOLED.setPixel(x + 6, y + 8);
  myOLED.setPixel(x + 7, y + 8);
  myOLED.setPixel(x + 6, y + 9);
  myOLED.setPixel(x + 7, y + 9);
  myOLED.setPixel(x + 6, y + 10);
  myOLED.setPixel(x + 7, y + 10);
  myOLED.setPixel(x + 6, y + 14);
  myOLED.setPixel(x + 7, y + 14);
  myOLED.setPixel(x + 6, y + 15);
  myOLED.setPixel(x + 7, y + 15);
  myOLED.setPixel(x + 6, y + 16);
  myOLED.setPixel(x + 7, y + 16);

  myOLED.setPixel(x + 7, y + 7);
  myOLED.setPixel(x + 6, y + 17);
}
