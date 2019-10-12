#include "MHZ19b.h"

MHZ19b::MHZ19b(int RX, int TX){
  swSerial = new SoftwareSerial(RX, TX);
  swSerial->begin(9600);

  byte setrangeA_cmd[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x13, 0x88, 0xCB};
  unsigned char setrangeA_response[9]; 
  swSerial->write(setrangeA_cmd,9);
  swSerial->readBytes(setrangeA_response, 9);
  byte setrangeA_crc = 0;
  for (int setrangeA_i = 1; setrangeA_i < 8; setrangeA_i++) setrangeA_crc+=setrangeA_response[setrangeA_i];
  setrangeA_crc = 255 - setrangeA_crc; setrangeA_crc++;
  
  if ( !(setrangeA_response[0] == 0xFF && setrangeA_response[1] == 0x99 && setrangeA_response[8] == setrangeA_crc) ) {
    init = false;
  } else {
    init = true;
  }
}

MHZ19b::~MHZ19b(){
  delete swSerial;
}

int MHZ19b::getInit(){
  return init;
}

result<int> MHZ19b::getCO2(){
  byte measure_cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  unsigned char measure_response[9]; 

  //Узнаём концентрацию CO2 через UART
  swSerial->write(measure_cmd,9);
  swSerial->readBytes(measure_response, 9);
  byte crc = 0;
  for (int i = 1; i < 8; i++) crc+=measure_response[i];
  crc = 255 - crc; crc++;
  if ( !(measure_response[0] == 0xFF && measure_response[1] == 0x86 && measure_response[8] == crc) ) {
    return result<int>(0, false);
  } 
  
  unsigned int responseHigh = (unsigned int) measure_response[2];
  unsigned int responseLow = (unsigned int) measure_response[3];
  unsigned long ppm = (256*responseHigh) + responseLow;

  return result<int>(ppm, true);
}
