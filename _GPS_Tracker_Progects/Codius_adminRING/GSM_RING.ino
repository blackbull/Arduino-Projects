void CheckGSM_RING() {

  if (SIM800.available())   {                         // Если модем, что-то отправил...
    _response = waitResponse();                       // Получаем ответ от модема для анализа
    _response.trim();                                 // Убираем лишние пробелы в начале и конце
    DEBUG_ln_2(_response);                        // Если нужно выводим в монитор порта
    if (_response.indexOf("+CMTI:") > -1) {           // Пришло сообщение об отправке SMS
      lastUpdate = millis() -  updatePeriod;          // Теперь нет необходимости обрабатываеть SMS здесь, достаточно просто
      // сбросить счетчик автопроверки и в следующем цикле все будет обработано
    }


    if (_response.startsWith("RING")) {         // Есть входящий вызов
      int phoneindex = _response.indexOf("+CLIP: \"");// Есть ли информация об определении номера, если да, то phoneindex>-1
      String innerPhone = "";                   // Переменная для хранения определенного номера
      if (phoneindex >= 0) {                    // Если информация была найдена
        phoneindex += 8;                        // Парсим строку и ...
        innerPhone = _response.substring(phoneindex, _response.indexOf("\"", phoneindex)); // ...получаем номер
        DEBUG_ln_2("Number: " + innerPhone); // Выводим номер в монитор порта
      }

      sendATCommand("ATH", true);        // отклоняем вызов
      // Проверяем, чтобы длина номера была больше 6 цифр, и номер должен быть в списке
      if (innerPhone.length() >= 7 && phones.indexOf(innerPhone) >= 0) {
        DEBUG_ln_1(F("SEND ansver in SMS"));      // Если да, то отвечаем смс
      }
    }
  }
}
