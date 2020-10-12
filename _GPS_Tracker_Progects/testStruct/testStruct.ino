#include <EEPROM.h>
//#define FistInitial

#define PhonesAdress 0 //0-39
#define OptionsStructAdress 40 //40-47
#define LastWritingStructAdress 48 //48-68
#define GPSstartAdress 72 //72-1024

String Phones = "111111111111_222222222222_333333333333"; //стартовый адрес 0

struct OptionsStruct { //стартовый адрес 40-47
  byte SleepMode = 0;

  byte LastWritingOPT_Adres = LastWritingStructAdress;
  long MaxWriteCount = 1000000;
  byte FistLoad = 200;
};

struct LastWritingStruct {//стартовый адрес 48-68
  int LastAdress = GPSstartAdress; //для хранения координат в структуре 69-1024
  long WriteCount = 0;
};

struct GpsDataStruct {//стартовый адрес 69-1024
  float LAT = 0;
  float LNG = 0;

  byte Speed = 0;
  byte Month = 0;
  byte Day = 0;

  byte Hour = 0;
  byte Min = 0;
  byte Sec = 0;

  byte StatusCode = 0;
};

OptionsStruct OptionsSTR;
LastWritingStruct LastWritingSTR;
GpsDataStruct GPSData;

void setup() {
  Serial.begin(9600);
  Serial.println(F("======================================================================"));

#ifdef FistInitial
  Serial.print("OptionsStruct size "); Serial.println(sizeof(OptionsStruct));
  Serial.print("LastWritingStruct size "); Serial.println(sizeof(LastWritingStruct));
  Serial.print("GpsDataStruct size "); Serial.println(sizeof(GpsDataStruct));
  Serial.println("-----------------------------------------");

  InitializingOptions();
  LoadFullOptions();
#endif

  LoadOptions(); //загрузить опции из ROM
  PrintlnFull_GPS_Data();
  String st = Get_Last_GPS_Data_String(10, 60); 

  Serial.println(st);
}


void loop() {

}
