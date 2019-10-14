#pragma once

#include <arduino.h>

#include "Adafruit_BME280.h"

#include "result.h"

class BME280{
public:
  bool init();
  bool getInit();
  result<float> getTemperature();
  result<float> getHumidity();
  result<float> getPressure();

private:
  static const double MBR_TO_MMHG = 0.75006168;

  Adafruit_BME280 sensor;
  bool initResult = false;
};
