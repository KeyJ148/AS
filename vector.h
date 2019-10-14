#pragma once

#include <arduino.h>

template<class T> 
class vector{
public:

  vector(int sizeArray) : sizeArray(sizeArray){
    val = new T[sizeArray];
  }
  
  vector(int sizeArray, T init) : vector(sizeArray){
    for(int i=0; i<sizeArray; i++) val[i] = init;
  }
  
  vector(int sizeArray, const T init[]) : vector(sizeArray){
    for(int i=0; i<sizeArray; i++) val[i] = init[i];
  }
  vector(const vector<T>& copy) : vector(copy.size()){
    for(int i=0; i<sizeArray; i++) val[i] = copy[i];
  }
  
  ~vector(){
    delete[] val;
  }
  
  int size(){
    return sizeArray;
  }
  
  T& operator[](int pos){
    return val[pos];
  }
  
private:
  T* val;  
  int sizeArray;
};
