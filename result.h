#pragma once

template<class T> 
struct result{
  T val;
  bool valid = true;
  
  result();
  result(T val) : val(val){};
  result(T val, bool valid) : val(val), valid(valid){};
};
