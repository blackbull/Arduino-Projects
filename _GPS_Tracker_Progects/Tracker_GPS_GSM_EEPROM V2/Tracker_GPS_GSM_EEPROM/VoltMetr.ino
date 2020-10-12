float GetBatVolt() {
  return (analogRead(pinBat) * RealVcc_arduino) / 1024.0;
}

float GetVccVolt() {
  return ((analogRead(pinVcc) * RealVcc_arduino) / 1024.0) / (R2 / (R1 + R2));
}
