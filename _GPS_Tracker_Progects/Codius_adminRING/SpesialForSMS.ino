String GetAllOptions () {
  return "Admin numbers: " + phones + "\nSomethig other options";
}

void sendSMS(String phone, String message) {
  sendATCommand("AT+CMGS=\"" + phone + "\"", true);             // Переходим в режим ввода текстового сообщения
  sendATCommand(message + "\r\n" + (String)((char)26), true);   // После текста отправляем перенос строки и Ctrl+Z
}
