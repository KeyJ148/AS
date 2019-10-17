#include <arduino.h>

#include "BME280.h"
#include "MHZ19b.h"
#include "package_sender.h"

BME280 bme;
MHZ19b mhz(A0, A1);
package_sender sender(package::getLength());

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
  
  package pack;
  pack.t = t.val;
  pack.h = h.val;
  pack.p = p.val;
  pack.co2 = co2.val;
  pack.bme_status = t.valid && h.valid && p.valid;
  pack.mhz_status = co2.valid;

  sender.setData(pack);
  sender.send();
  
  delay(5*1000);
}
