#pragma once

#include <arduino.h>
#include <SoftwareSerial.h>

#include "result.h"
#include "vector.h"

class MHZ19b{
public:
  MHZ19b(int, int);
  ~MHZ19b();
  bool getInit();
  bool setABC(bool);
  result<int> getCO2();

private:
  SoftwareSerial* swSerial;
  bool init;

  result<vector<byte>> sendCommand(const byte []);
  bool checkResponse(const byte []);
};
