#include "MHZ19b.h"

const byte MHZ19b::INIT_MAX_5000[] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x13, 0x88, 0xCB};
const byte MHZ19b::ABC_ON[] =        {0xFF, 0x01, 0x79, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xE6};
const byte MHZ19b::ABC_OFF[] =       {0xFF, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86};
const byte MHZ19b::GET_CO2[] =       {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

MHZ19b::MHZ19b(int RX, int TX) : RX(RX), TX(TX){
  swSerial = new SoftwareSerial(RX, TX);
}

MHZ19b::~MHZ19b(){
  delete swSerial;
}

bool MHZ19b::init(){
  swSerial->begin(9600);  
  initResult = sendCommand(INIT_MAX_5000).valid;
  
  return initResult;
}

bool MHZ19b::getInit(){
  return initResult;
}

bool MHZ19b::setABC(bool abc){
  return sendCommand((abc)? ABC_ON : ABC_OFF).valid;
}

result<int32_t> MHZ19b::getCO2(){
  result<vector<byte>> response = sendCommand(GET_CO2);
  
  int32_t responseHigh = response.val[2];
  int32_t responseLow = response.val[3];
  int32_t ppm = (256*responseHigh) + responseLow;

  return result<int32_t>(ppm, response.valid);
}

result<vector<byte>> MHZ19b::sendCommand(const byte command[]){
  swSerial->write(command, 9);
  
  byte response[9];
  swSerial->readBytes(response, 9);
  
  return result<vector<byte>>(vector<byte>(9, response), checkResponse(command[2], response));
}

bool MHZ19b::checkResponse(byte commandID, const byte response[]){
  byte crc = 0;
  for (int i = 1; i < 8; i++) crc += response[i];
  crc = 255 - crc; crc++;
  
  return (response[0] == 0xFF && response[1] == commandID && response[8] == crc);
}
