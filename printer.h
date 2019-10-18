#pragma once

#include <arduino.h>

#include "package_sender.h"

class printer{
public:
  static const int MODE_IGNORE = 0, MODE_STRING = 1, MODE_PLOTTER = 2, MODE_HASH = 3; 

  printer(int);
  void print(float, float, float, int32_t, byte, byte);
  
private:
  int mode;
  void print_string(float, float, float, int32_t, byte, byte);
  void print_plotter(float, float, float, int32_t, byte, byte);
  void print_hash(float, float, float, int32_t, byte, byte);
};
