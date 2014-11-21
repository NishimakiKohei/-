
#pragma once

//
// 乱数
//
//#define USE_RAND 0
#include "defines.hpp"


#ifdef USE_RAND 
#include <random>


class Random {
  std::mt19937 engine_;
  std::uniform_real_distribution<float> dist_zero_to_one_;

  
public:
  Random();


  void setSeed(const u_int new_seed);
  
  // [0, last) を返す
  int fromZeroToLast(const int last);

  // [first, last] を返す
  int fromFirstToLast(const int first, const int last);
  
  // [0.0f, 1.0f] を返す
  float fromZeroToOne();

  // [first, last] を返す
  float fromFirstToLast(const float first, const float last);
  
};
#endif