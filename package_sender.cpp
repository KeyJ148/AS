#include "package_sender.h"

package_sender::package_sender(int lengthData){
  this->lengthData = lengthData;
  buf = new byte[getLength()];
}

package_sender::package_sender(const package_sender& sender){
  buf = new byte[sender.getLength()];
  for(int i=0; i<sender.getLength(); i++) buf[i] = sender.buf[i];
}

void package_sender::setData(const package& pack){
  intToByteArray(SEPARATOR, buf);
  pack.writeBytes(buf+LENGTH_SEPARATOR);
  intToByteArray(getHash(), buf+LENGTH_SEPARATOR+lengthData);
}

void package_sender::send(){
  Serial.write(getBytes(), getLength());
}

byte* package_sender::getBytes(){
  return buf;
}

int package_sender::getLength(){
  return LENGTH_SEPARATOR+lengthData+LENGTH_HASH;
}

int32_t package_sender::getHash(){
  int32_t hash = 0;
  int32_t pow_val = 1;
  
  for (int i = LENGTH_SEPARATOR; i < LENGTH_SEPARATOR+lengthData; i++){
    hash = hash + ((int32_t) buf[i])*pow_val;   
    pow_val = pow_val * P;
  }
    
  return hash;
}
  
package_sender::~package_sender(){
  delete[] buf;
}

void intToByteArray(int32_t val, byte* b){
  byte* p = reinterpret_cast<byte*>(&val);
  for (int i = 0; i < 4; ++i) b[3-i] = p[i];
}

void floatToByteArray(float val, byte* b){
  byte* p = reinterpret_cast<byte*>(&val);
  for (int i = 0; i < 4; ++i) b[i] = p[i];
}

int32_t byteArrayToInt(byte* b){
  int32_t res = 0;
  for(int i=0; i<4; i++){
    res |= static_cast<int>(b[i]) << 32-(i+1)*8;
  }

  return res;
}
