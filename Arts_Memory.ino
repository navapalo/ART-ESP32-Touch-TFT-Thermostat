// Wouldnt that be Great if Art can remember Things
// Read from Arts memory and write into Arts memory
// 
// touch calibrate setting save has already formatted Arts Brain if needed 
//
// Use new brain-file for Art => file = "/Arts_Memory"; 
//
//***************************
// what do we want to save
//***************************
// eco setpoint
// normal setpoint
// cool setpoint
// switchpoint above / below
// alarm setpoints low/high
// screen brightnes
//
// auto mode  program & times temps
//
// Arts age ;-) time since startdate / memory creation?
//
//
//
//
//
//copy this ino for testing in a blank arduino ide
//and upload to esp32 see in serial monitor result so far
//
// mostly code from the ARDUINO ESP32 Examples SPIFFS test
// ESP32 Read Write variables to SPIFFS
// Working on it, so far this is it, write 11 valeus and read 11 values
// directory listing and values
//
// outputs data on serial terminal 115200
//
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat

#include "FS.h"
#include "SPIFFS.h"
int CharRead;
char CharArray[16];
/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED 1

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.println("now in begin of list directory");
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}




void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("now in begin of setup");
  Serial.println(); Serial.println();

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
}






void loop() {
  Serial.println("now in begin of loop");
  Serial.println(); Serial.println();

  listDir(SPIFFS, "/", 0);
  Serial.println("ListDir 5 second delay");
  delay(5000);
  File  file = SPIFFS.open("/ART_Thermostat.txt", FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  } else {
    file.println("1");
    file.println("22");
    file.println("1111");
    file.println("11114");
    file.println("1555");
    file.println("881111111");
    file.println("1111111");
    file.println("16611.111");
    file.println("11.111");
    file.close();
    Serial.println("done writing into arts memory file");
  }

  Serial.println("5 second delay");
  delay(5000);
  Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println();






  File readfile = SPIFFS.open("/ART_Thermostat.txt");
  if (!readfile || readfile.isDirectory()) {
    Serial.println("no good");
    return;
  }

  Serial.println("got acces to Arts memory, going to read his brain / memory");
  int i = 1;
  String ThisString;
  while (readfile.available()) {

    CharRead = (readfile.read());

    if (CharRead == 10) {  //linefeed
      Serial.println(" line feed");
      Serial.print("CharArray=>"); Serial.print(CharArray); Serial.println("<=end");

      Serial.print("ThisString.toInt() "); Serial.println(ThisString.toInt());
      Serial.print("ThisString.toFloat() "); Serial.println(ThisString.toFloat());
      memset(CharArray, 0, sizeof(CharArray));//clear array
    }

    if (CharRead == 13) {
      Serial.print(" carriage return ");
      ThisString = "";

      i = 0;
      delay(2500);
    }

    Serial.print(char(CharRead)); delay(50);
    CharArray[i] = char(CharRead);
    ThisString = String(CharArray);
    i = i + 1;
  }

  Serial.println("done reading file");
  Serial.println( "Test complete" );
  Serial.println("5 second delay");
  delay(5000);


  Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println();
  Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println();

}