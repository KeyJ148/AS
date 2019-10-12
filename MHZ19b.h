#pragma once

#include <arduino.h>
#include <SoftwareSerial.h>

template<class T> 
struct result{
  T val;
  bool valid = true;
  
  result();
  result(T val) : val(val){};
  result(T val, bool valid) : val(val), valid(valid){};
};

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
