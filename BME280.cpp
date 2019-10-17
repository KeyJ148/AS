#include "BME280.h";

bool BME280::init(){
  initResult = sensor.begin();
  return initResult;
}

bool BME280::getInit(){
  return initResult;
}

result<float> BME280::getTemperature(){
  float t = sensor.readTemperature();
  return result<float>(t, !isnan(t) && t > -100 && t < 100);
}

result<float> BME280::getHumidity(){
  float h = sensor.readHumidity();
  return result<float>(h, !isnan(h) && h > 1 && h < 99);
}

result<float> BME280::getPressure(){
  float p = sensor.readPressure() / 100 * MBR_TO_MMHG;
  return result<float>(p, !isnan(p) && p > 640 && p < 810);
}
