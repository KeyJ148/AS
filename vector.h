#pragma once

#include <arduino.h>

template<class T> 
class vector{
public:
  vector(int);
  vector(int, T);
  vector(int, const T []);
  vector(const vector&);
  ~vector();
  
  int size();
  T& operator[](int);
  
private:
  T* val;  
  int sizeArray;
};
