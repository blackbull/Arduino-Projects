
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//#include <SPI.h>//?????????????????????????????????????????????????????????
#include <SD.h>
//#include <EEPROMex.h>
//==============================================================


//==============================================================
TinyGPSPlus gps;
SoftwareSerial GPS_Port(6, 5);
//==============================================================

float  last_LAT, last_LNG;                // переменные расстояния
//TinyGPSDate dd;
//TinyGPSTime tt;

bool SD_Enabled = false;      //SD установлено и нормально инициализировано
bool FreshGPSData = false;    //свежие данные с GPS получены и обработаны
//==============================================================
