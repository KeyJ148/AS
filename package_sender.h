#pragma once

#include "defines.h"

void intToByteArray(int, byte*);
void floatToByteArray(float, byte*);
int byteArrayToInt(byte*);

struct package{
  //Все добавленные поля необходимо дописать в writeBytes(), а их размер проссумировать в PACKAGE_SIZE
  
  float t;
  float h;
  float p;
  byte bme_status;

  static const int PACKAGE_SIZE = 4+4+4+1;
  void writeBytes(byte* buf){
    floatToByteArray(t, buf);
    floatToByteArray(h, buf+4);
    floatToByteArray(p, buf+8);
    buf[12] = bme_status;
  }

  static int getLength(){
    return PACKAGE_SIZE;
  }
};

class package_sender{
private: 
  const int LENGTH_SEPARATOR = 4;
  const int LENGTH_HASH = 4;
  const int SEPARATOR = 0xAA9999AA;
  const int P = 1000000007;

  int lengthData;
  byte* buf;

public:
  package_sender(int);
  package_sender(const package_sender&);
  ~package_sender();
  
  void setData(const package&);
  void send();
  byte* getBytes();
  int getLength();
  int getHash();
};
