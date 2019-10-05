#pragma once

#include <arduino.h>
#include <SoftwareSerial.h>

class MHZ19b{
private:
  SoftwareSerial* swSerial;
  bool init;
  bool status;
public:
  MHZ19b();
  ~MHZ19b();
  int getCO2();
};
