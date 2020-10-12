#include "EEPROM.h"

void setup()
{
  // Проход всех ячеек(байтов) и запись в них чисел 255.
  for (int i = 0; i < EEPROM.length(); i++) EEPROM.update(i, 255);
}

void loop()
{
  // Пустой цикл...
}
