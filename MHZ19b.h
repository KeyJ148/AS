#pragma once

#include <arduino.h>
#include <SoftwareSerial.h>

#include "result.h"

class MHZ19b{
private:
  SoftwareSerial* swSerial;
  bool init;
public:
  MHZ19b(int, int);
  ~MHZ19b();
  int getInit();
  result<int> getCO2();
};
