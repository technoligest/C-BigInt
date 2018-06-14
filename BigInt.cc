//
// Created by Yaser Alkayale on 2018-06-06.
//

#include "BigInt.h"

namespace bigint{


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
void BigInt::add(const vector<ull> &num1, const vector<ull> &num2, vector<ull> &result) const {
  result.clear();
  int i;
  int carry = 0;
  for(i = 0; i < num1.size() && i < num2.size(); ++i) {
    ull n1 = num1[i];
    ull n2 = num2[i];
    ull remainder = std::numeric_limits<ull>::max() - n2;

    result.push_back(n1 + n2 + carry);

    /*
     * overflow is detected if
     * 1- n1 is larger than the difference between n2 and max<ull>
     * 2- otherwise, there is overflow if the difference is the same as n1 ans there is a previous carry.
     */
    if(n1 > remainder || (n1 == remainder && carry == 1)) {
      carry = 1;
    } else {
      carry = 0;
    }
  }

  const vector<ull> &bigger = (i < num1.size()) ? num1 : num2;

  if(carry == 1) {
    for(; i < bigger.size() && bigger[i] == std::numeric_limits<ull>::max(); ++i) {
      result.push_back(0);
    }
    if(i == bigger.size()) {
      result.push_back(1);
    } else {
      result.push_back(bigger[i] + 1);
      ++i;
    }
  }

  for(; i < bigger.size(); ++i) {
    result.push_back(bigger[i]);
  }
}
BigInt &BigInt::operator+=(const BigInt &toAdd) {
  if((this->isPositive_ && !toAdd.isPositive_) ||
     (!this->isPositive_ && toAdd.isPositive_)) {
    BigInt toAddAbsolute(toAdd);
    toAddAbsolute.isPositive_ = true;
    if((*this) > toAddAbsolute) {
      vector<ull> temp;
      difference(fullInteger_, toAdd.fullInteger_, temp);
      fullInteger_ = std::move(temp);
    } else {
      vector<ull> temp;
      difference(toAdd.fullInteger_, fullInteger_, temp);
      fullInteger_ = std::move(temp);
      isPositive_ = !isPositive_;
    }
  } else {
    vector<ull> additionResult;
    add(fullInteger_, toAdd.fullInteger_, additionResult);
    fullInteger_ = std::move(additionResult);

    if(!isPositive_ && !toAdd.isPositive_) {
      isPositive_ = false;
    }
  }
  return *this;
}
BigInt operator+(BigInt lhs, const BigInt &rhs) // otherwise, both parameters may be const references
{
  lhs += rhs; // reuse compound assignment
  return lhs; // return the result by value (uses move constructor)
}
BigInt &BigInt::operator++() {
  (*this) += 1;
  return *this;
}
BigInt BigInt::operator++(int) {
  BigInt tmp(*this);
  (*this) += 1;
  return tmp;
}


BigInt &BigInt::operator--() {
  //TODO Implement
  //(*this) -= 1;
  return *this;
}
BigInt BigInt::operator--(int) {
  //TODO Implement
  BigInt tmp(*this);
  //(*this) -= 1;
  return tmp;
}

//Using the double dabble algorithm, based on Wikipedia C code
std::string BigInt::toString() const {
  std::vector<char> result(1);
  int bitToShift = 0;
  for(int i = fullInteger_.size() - 1; i >= 0; --i) {
    for(int j = sizeof(ull) * 8 - 1; j >= 0; --j) {
      if((fullInteger_[i] & (1ULL << j)) > 0) {
        bitToShift = 1;
      } else {
        bitToShift = 0;
      }
      for(int k = 0; k < result.size(); ++k) {
        if(result[k] >= 5) {
          result[k] += 3;
        }
      }
      if(result[result.size() - 1] >= 8) {
        result.push_back(0);
      }
      for(int k = result.size() - 1; k > 0; --k) {
        result[k] <<= 1;
        result[k] &= 0xF;
        result[k] |= result[k - 1] >= 8;
      }
      result[0] <<= 1;
      result[0] &= 0xF;
      result[0] |= bitToShift;
    }
  }

  int last = result.size() - 1;
  while(result[last] == 0) {
    --last;
  }

  for(int i = last; i >= 0; --i) {
    result[i] += '0';
  }

  return std::string(result.begin(), result.end());
}

bool operator==(const BigInt &int1, const BigInt &int2) {
  if(int1.fullInteger_.empty() && int1.fullInteger_.empty()) return true;
  if(int1.fullInteger_.size() != int2.fullInteger_.size()) return false;
  if(int1.isPositive_ != int2.isPositive_) return false;
  for(int i = 0; i < int1.fullInteger_.size(); ++i) {
    if(int1.fullInteger_[i] != int2.fullInteger_[i]) {
      return false;
    }
  }
  return true;
}


}//namespace bigint;