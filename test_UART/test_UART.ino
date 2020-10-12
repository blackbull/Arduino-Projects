void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start from slave");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Send22");
  delay(1000);
/*
  if (Serial.available())           // Ожидаем команды по Serial...
  {
    Serial.write(Serial.read());
  }*/
}
