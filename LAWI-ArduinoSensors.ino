#include "DHT.h"
#include "Adafruit_BME280.h"

#include "package_sender.h"
#include "defines.h"

Adafruit_BME280 bme;
bool bme_init;

package_sender sender(package::getLength());

void setup() {
  Serial.begin(9600);
  
  bme_init = bme.begin();
  while (!Serial);
}

void loop() {
  float t = 0, h = 0, p = 0;
  bool bme_status = 1;
  
  if (bme_init){
    t = bme.readTemperature();
    h = bme.readHumidity();
    p = bme.readPressure() / 100 * MBR_TO_MMHG;

    if (isnan(t)) bme_status = 0;
    if (isnan(h) || h == 0) bme_status = 0;
    if (isnan(p) || p == 0) bme_status = 0;
  } else {
    bme_status = 0;
  }

  package pack;
  pack.t = t;
  pack.h = h;
  pack.p = p;
  pack.bme_status = bme_status;

  sender.setData(pack);
  sender.send();

  delay (10*1000);
}
