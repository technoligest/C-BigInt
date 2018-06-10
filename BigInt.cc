//
// Created by Yaser Alkayale on 2018-06-06.
//

#include "BigInt.h"

namespace bigint{
template<typename T, typename>
BigInt::BigInt(T baseInteger) {
  if(baseInteger == (T) 0) {
    isPositive_ = true;
  } else if(baseInteger < ((T) 0)) {
    isPositive_ = false;
    fullInteger_.push_back((ull) (baseInteger * -1));
  } else {
    isPositive_ = true;
    fullInteger_.push_back(baseInteger);
  }
}
bool operator==(const BigInt &int1, const BigInt &int2) {
  std::cout << "got here" << std::endl;
  if(int1.fullInteger_.empty() && int1.fullInteger_.empty()) return true;
  if(int1.fullInteger_.size() != int2.fullInteger_.size()) return false;
  if(int1.isPositive_ != int2.isPositive_) return false;
  std::cout << int1.toString() << "+++" << int2.toString() << std::endl;
  for(int i = 0; i < int1.fullInteger_.size(); ++i) {
    if(int1.fullInteger_[i] != int2.fullInteger_[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(const BigInt &int1, const BigInt &int2) {
  return !(int1 == int2);
}
bool BigInt::operator>(const BigInt &int2) const {
  if((*this).isPositive_ && !int2.isPositive_) {
    return true;
  } else if(!(*this).isPositive_ && int2.isPositive_) {
    return false;
  } else if((*this).isPositive_ && int2.isPositive_) {
    if((*this).fullInteger_.size() > int2.fullInteger_.size()) {
      return true;
    }
    if((*this).fullInteger_.size() < int2.fullInteger_.size()) {
      return false;
    }
    for(int i = (*this).fullInteger_.size() - 1; i >= 0; --i) {
      if((*this).fullInteger_[i] < int2.fullInteger_[i]) {
        return false;
      }
    }
    return true;
  } else if(!(*this).isPositive_ && !int2.isPositive_) {
    if((*this).fullInteger_.size() > int2.fullInteger_.size()) {
      return false;
    }
    if((*this).fullInteger_.size() < int2.fullInteger_.size()) {
      return true;
    }
    for(int i = (*this).fullInteger_.size() - 1; i >= 0; --i) {
      if((*this).fullInteger_[i] < int2.fullInteger_[i]) {
        return true;
      }
    }
    return false;
  }
  assert(false);
  return true;
}
bool BigInt::operator<(const BigInt &int2) const {
  return int2 > (*this);
}
bool BigInt::operator>=(const BigInt &int2) const {
  return !((*this) < int2);
}
bool BigInt::operator<=(const BigInt &int2) const {
  return !((*this) > int2);
}
//TODO change this implementation so that the first does not have to be bigger than the second one.

void BigInt::difference(vector<ull> num1, const vector<ull> &num2, vector<ull> &result) const {
  assert(num1.size() >= num2.size());

  result.clear();
  int i;
  for(i = 0; i < num2.size(); ++i) {
    if(num1[i] > num2[i]) {
      result.push_back(num1[i] - num2[i]);
    } else {
      assert(i < num1.size() - 1);
      assert(num1[i + 1] > 0);
      /*
       * Guaranteed no overflow because num2[i]>num1[i]
       */
      result.push_back(std::numeric_limits<ull>::max() - num2[i] + 1 + num1[i]);


      /*
       * This is only okay because num1>num2
       */
      --num1[i + 1];
    }
  }
  while(i++ < num1.size()) {
    result.push_back(num1[i]);
  }
}

//To pringt a bigInt object (toString)
inline std::ostream &operator<<(std::ostream &out, BigInt &integer) {
  out << integer.toString();
  return out;
}

}//namespace bigint;