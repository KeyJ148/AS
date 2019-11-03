#include <arduino.h>

#include "BME280.h"
#include "MHZ19b.h"
#include "printer.h"

BME280 bme;
MHZ19b mhz(A0, A1);
printer printerToUSB(printer::MODE_HASH);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  mhz.init(); mhz.setABC(false);
  bme.init();
}

void loop() {
  result<float> t = (bme.getInit())? bme.getTemperature() : result<float>(0, false);
  result<float> h = (bme.getInit())? bme.getHumidity() : result<float>(0, false);
  result<float> p = (bme.getInit())? bme.getPressure() : result<float>(0, false);
  result<int32_t> co2 = (mhz.getInit())? mhz.getCO2() : result<int32_t>(0, false);

  printerToUSB.print(t.val, h.val, p.val, co2.val, (t.valid && h.valid && p.valid), co2.valid);
  delay(5*1000);
}
