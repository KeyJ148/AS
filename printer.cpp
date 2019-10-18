#include "printer.h"

printer::printer(int mode) : mode(mode){}

void printer::print(float t, float h, float p, int32_t co2, byte bme_status, byte mhz_status){
  switch(mode){
    case 1: print_string(t, h, p, co2, bme_status, mhz_status); break;
    case 2: print_plotter(t, h, p, co2, bme_status, mhz_status); break;
    case 3: print_hash(t, h, p, co2, bme_status, mhz_status); break;
  }
}

void printer::print_string(float t, float h, float p, int32_t co2, byte bme_status, byte mhz_status){
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C");
  Serial.println((bme_status)? "" : " (Not valid!)");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %");
  Serial.println((bme_status)? "" : " (Not valid!)");
  
  Serial.print("Pressure: ");
  Serial.print(p);
  Serial.print(" mm Hg");
  Serial.println((bme_status)? "" : " (Not valid!)");
  
  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print(" ppm");
  Serial.println((mhz_status)? "" : " (Not valid!)");
  
  Serial.println();
}

void printer::print_plotter(float t, float h, float p, int32_t co2, byte bme_status, byte mhz_status){
  Serial.print(t*10);
  Serial.print(" ");
  Serial.print(h*10);
  Serial.print(" ");
  Serial.print(p);
  Serial.print(" ");
  Serial.print(co2);
  Serial.println();
}

void printer::print_hash(float t, float h, float p, int32_t co2, byte bme_status, byte mhz_status){
  package pack;
  pack.t = t;
  pack.h = h;
  pack.p = p;
  pack.co2 = co2;
  pack.bme_status = bme_status;
  pack.mhz_status = mhz_status;

  package_sender sender(package::getLength());
  sender.setData(pack);
  sender.send();
}
