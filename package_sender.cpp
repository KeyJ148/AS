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

int package_sender::getHash(){
  int hash = 0;
  int pow_val = 1;
  
  for (int i = LENGTH_SEPARATOR; i < LENGTH_SEPARATOR+lengthData; i++){
    hash = hash + ((int) buf[i])*pow_val;   
    pow_val = pow_val * P;
  }
    
  return hash;
}
  
package_sender::~package_sender(){
  delete[] buf;
}

void intToByteArray(int val, byte* b){
  b[0] = (val & 0xff000000) >> 24;
  b[1] = (val & 0x00ff0000) >> 16;
  b[2] = (val & 0x0000ff00) >> 8;
  b[3] = (val & 0x000000ff) >> 0;
}

void floatToByteArray(float val, byte* b){
  byte* p = reinterpret_cast<byte*>(&val);
  for (int i = 0; i < 4; ++i) b[i] = p[i];
}

int byteArrayToInt(byte* b){
  int res = 0;
  for(int i=0; i<4; i++){
    res |= static_cast<int>(b[i]) << 32-(i+1)*8;
  }

  return res;
}
