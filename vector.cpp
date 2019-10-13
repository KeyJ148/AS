#include "vector.h"

template<class T> 
vector<T>::vector(int sizeArray) : sizeArray(sizeArray){
  val = new T[sizeArray];
}

template<class T> 
vector<T>::vector(int sizeArray, T init) : vector(sizeArray){
  for(int i=0; i<sizeArray; i++) val[i] = init;
}

template<class T> 
vector<T>::vector(int sizeArray, const T init[]) : vector(sizeArray){
  for(int i=0; i<sizeArray; i++) val[i] = init[i];
}

template<class T> 
vector<T>::vector(const vector& copy) : vector(copy.size()){
  for(int i=0; i<sizeArray; i++) val[i] = copy[i];
}

template<class T> 
vector<T>::~vector(){
  delete[] val;
}

template<class T> 
int vector<T>::size(){
  return sizeArray;
}

template<class T> 
T& vector<T>::operator[](int pos){
  return &val[pos];
}
