#include "MHZ19b.h"

MHZ19b::MHZ19b(int RX, int TX){
  swSerial = new SoftwareSerial(RX, TX);
  swSerial->begin(9600);

  init = sendCommand(INIT_MAX_5000).valid;
}

MHZ19b::~MHZ19b(){
  delete swSerial;
}

bool MHZ19b::getInit(){
  return init;
}

bool MHZ19b::setABC(bool abc){
  return sendCommand((abc)? ABC_ON : ABC_OFF).valid;
}

result<int> MHZ19b::getCO2(){
  result<vector<byte>> response = sendCommand(INIT_MAX_5000);
  
  unsigned int responseHigh = (unsigned int) response.val[2];
  unsigned int responseLow = (unsigned int) response.val[3];
  unsigned long ppm = (256*responseHigh) + responseLow;

  return result<int>(ppm, response.valid);
}

result<vector<byte>> MHZ19b::sendCommand(const byte command[]){
  if (sizeof(command) != 9) return result<vector<byte>>(vector<byte>(0), false);
  swSerial->write(command, 9);
  
  unsigned char response[9];
  swSerial->readBytes(response, 9);

  return result<vector<byte>>(vector<byte>(9, response), checkResponse(command[2], response));
}

bool MHZ19b::checkResponse(byte commandID, const byte response[]){
  if (sizeof(response) != 9) return false;

  byte crc = 0;
  for (int i = 1; i < 8; i++) crc += response[i];
  crc = 255 - crc; crc++;
  
  return !(response[0] == 0xFF && response[1] == commandID && response[8] == crc);
}
