#pragma once

#include <arduino.h>
#include <SoftwareSerial.h>

#include "result.h"
#include "vector.h"

class MHZ19b{
public:
  MHZ19b(int, int);
  ~MHZ19b();

  bool init();
  bool getInit();
  bool setABC(bool);
  result<int> getCO2();

private:
  static const byte INIT_MAX_5000[], ABC_ON[], ABC_OFF[], GET_CO2[];

  SoftwareSerial* swSerial;
  bool initResult = false;
  int RX, TX;

  result<vector<byte>> sendCommand(const byte []);
  bool checkResponse(byte, const byte []);
};
