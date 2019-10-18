#pragma once

#include <arduino.h>

void intToByteArray(int32_t, byte*);
void floatToByteArray(float, byte*);
int32_t byteArrayToInt(byte*);

struct package{
  //Все добавленные поля необходимо дописать в writeBytes(), а их размер проссумировать в PACKAGE_SIZE
  
  float t;
  float h;
  float p;
  int32_t co2;
  byte bme_status;
  byte mhz_status;

  static const int PACKAGE_SIZE = 4+4+4+4+1+1;
  void writeBytes(byte* buf){
    floatToByteArray(t, buf);
    floatToByteArray(h, buf+4);
    floatToByteArray(p, buf+8);
    intToByteArray(co2, buf+12);
    buf[16] = bme_status;
    buf[17] = mhz_status;
  }

  static int getLength(){
    return PACKAGE_SIZE;
  }
};

class package_sender{
public:
  package_sender(int);
  package_sender(const package_sender&);
  ~package_sender();
  
  void setData(const package&);
  void send();
  byte* getBytes();
  int getLength();
  int32_t getHash();
  
private: 
  const int LENGTH_SEPARATOR = 4;
  const int LENGTH_HASH = 4;
  const int32_t SEPARATOR = 0xAA9999AA;
  const int32_t P = 1000000007;

  int lengthData;
  byte* buf;
};
