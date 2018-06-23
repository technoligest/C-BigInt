//
// Created by Yaser Alkayale on 2018-06-06.
//

#include "BigInt.h"

namespace bigint{

bool BigInt::firstIsBiggerThanSecond(const vector<ull> &num1, const vector<ull> &num2) const {
  if(num1.size() > num2.size()) {
    return true;
  }
  if(num1.size() < num2.size()) {
    return false;
  }
  int i;
  for(i = num1.size() - 1; i >= 0; --i) {
    if(num1[i] != num2[i]) {
      return num1[i] > num2[i];
    }
  }
  return false;
}

bool BigInt::operator>(const BigInt &int2) const {
  if(this->isPositive_ && !int2.isPositive_) {
    return true;
  } else if(!this->isPositive_ && int2.isPositive_) {
    return false;
  } else if(this->isPositive_ && int2.isPositive_) {
    return firstIsBiggerThanSecond(this->fullInteger_, int2.fullInteger_);
  } else if(!this->isPositive_ && !int2.isPositive_) {
    return firstIsBiggerThanSecond(int2.fullInteger_, this->fullInteger_);
  }
  assert(false);
  return true;
}
bool BigInt::operator<(const BigInt &int2) const {
  return int2 > (*this);
}
bool BigInt::operator>=(const BigInt &int2) const {
  return !this->operator<(int2);
}
bool BigInt::operator<=(const BigInt &int2) const {
  return !this->operator>(int2);
}




//TODO change this implementation so that the first does not have to be bigger than the second one.

vector<ull> BigInt::difference(vector<ull> num1, const vector<ull> &num2) const {
  assert(num1 >= num2);
  vector<ull> result;

  int i;
  for(i = 0; i < num2.size(); ++i) {
    if(num1[i] >= num2[i]) {
      result.push_back(num1[i] - num2[i]);
    } else {
      /*
       * Guaranteed no overflow because num2[i]>num1[i]
       */
      result.push_back(std::numeric_limits<ull>::max() - num2[i] + 1 + num1[i]);
      int temp = i;
      while(num1[temp] == 0) {
        num1[temp] = std::numeric_limits<ull>::max();
        ++temp;
      }
      /*
       * This is only okay because num1>num2
       */
      --num1[temp];
    }
  }
  while(i < num1.size()) {
    result.push_back(num1[i]);
    ++i;
  }
  return result;
}
vector<ull> BigInt::add(const vector<ull> &num1, const vector<ull> &num2) const {
  vector<ull> result;
  int i;
  int carry = 0;
  for(i = 0; i < num1.size() && i < num2.size(); ++i) {
    const ull &n1 = num1[i];
    const ull &n2 = num2[i];
    const ull &remainder = std::numeric_limits<ull>::max() - n2;

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
    while(i < bigger.size() && bigger[i] == std::numeric_limits<ull>::max()) {
      result.push_back(0);
      ++i;
    }
    if(i == bigger.size()) {
      result.push_back(1);
    } else {
      result.push_back(bigger[i] + 1);
      ++i;
    }
  }
  while(i < bigger.size()) {
    result.push_back(bigger[i]);
    ++i;
  }
  return result;
}
BigInt &BigInt::operator-=(const BigInt &toAdd) {
  if(this->isPositive_ != toAdd.isPositive_) {
    this->fullInteger_ = add(fullInteger_, toAdd.fullInteger_);
  } else {
    if(fullInteger_ == toAdd.fullInteger_) {
      fullInteger_ = {0};
      this->isPositive_ = true;
      return *this;
    }
    const bool &firstIsBigger = firstIsBiggerThanSecond(fullInteger_, toAdd.fullInteger_);
    const BigInt &bigger = firstIsBigger ? *this : toAdd;
    const BigInt &smaller = firstIsBigger ? toAdd : *this;
    this->fullInteger_ = difference(bigger.fullInteger_, smaller.fullInteger_);
    if(!firstIsBigger) {
      this->isPositive_ = !this->isPositive_;
    }
  }
  return *this;
}

BigInt &BigInt::operator+=(const BigInt &toAdd) {
  if(this->isPositive_ == toAdd.isPositive_) {
    fullInteger_ = add(fullInteger_, toAdd.fullInteger_);
  } else {
    if(fullInteger_ == toAdd.fullInteger_) {
      fullInteger_ = {0};
      this->isPositive_ = true;
      return *this;
    }
    const bool &firstIsBigger = firstIsBiggerThanSecond(fullInteger_, toAdd.fullInteger_);
    const BigInt &bigger = firstIsBigger ? *this : toAdd;
    const BigInt &smaller = firstIsBigger ? toAdd : *this;
    this->fullInteger_ = difference(bigger.fullInteger_, smaller.fullInteger_);
    if(!firstIsBigger) {
      this->isPositive_ = !this->isPositive_;
    }
  }
  return *this;
}

BigInt operator-(BigInt lhs, const BigInt &rhs) {
  lhs -= rhs;
  return lhs;
}
BigInt operator+(BigInt lhs, const BigInt &rhs) {
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
  assert(!fullInteger_.empty());
  if(fullInteger_.size() == 1) {
    if(isPositive_) {
      return std::to_string(fullInteger_[0]);
    } else {
      return std::string("-") + std::to_string(fullInteger_[0]);
    }

  }
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
  if(isPositive_) {
    return std::string(result.rbegin(), result.rend());
  } else {
    return std::string("-") + std::string(result.rbegin(), result.rend());
  }
}

bool operator==(const BigInt &int1, const BigInt &int2) {
  if(int1.fullInteger_.size() != int2.fullInteger_.size()) {
    return false;
  }
  if(int1.isPositive_ != int2.isPositive_) {
    return false;
  }
  for(int i = 0; i < int1.fullInteger_.size(); ++i) {
    if(int1.fullInteger_[i] != int2.fullInteger_[i]) {
      return false;
    }
  }
  return true;
}
string BigInt::divByTwo(const string &s) {
  if(s == "0" || s == "1") {
    return "0";
  }
  string newString("");
  int toAdd = 0;
  for(const char &ch:s) {
    assert(std::isdigit(ch));
    newString += std::to_string((toDigit(ch) / 2 + toAdd));
    toAdd = ((int) ch) % 2 == 1 ? 5 : 0;
  }
  if(newString[0] == '0') {
    newString.erase(0, 1);
  }
  return newString;
}
string BigInt::convertToBinary(string num) {
  if(num == "0") {
    return string("0");
  } else {
    string result("");
    while(num != "0") {
      result = string((int) num[num.size() - 1] % 2 == 1 ? "1" : "0") + result;
      num = divByTwo(num);
    }
    return result;
  }
}
ull BigInt::stringToUll(const string s) {
  ull result = 0ULL;
  for(int i = 0; i < s.size(); ++i) {
    assert(s[i] == '1' || s[i] == '0');
    result <<= 1;
    if(s[i] == '1') {
      result |= 1;
    }
  }
  return result;
}


}//namespace bigint;