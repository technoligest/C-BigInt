//
// Created by Yaser Alkayale on 2018-06-06.
//

#include "BigInt.h"

namespace bigint{

bool BigInt::firstIsBiggerThanSecond(const vector<ull> &num1, const vector<ull> &num2) const{
  if(num1.size() > num2.size()){
    return true;
  }
  if(num1.size() < num2.size()){
    return false;
  }
  ull i;
  for(i = num1.size() - 1;; --i){
    if(num1[i] != num2[i]){
      return num1[i] > num2[i];
    }
    if(i == 0ULL){
      return false;
    }
  }
  assert(false);
}

bool BigInt::operator>(const BigInt &int2) const{
  if(this->isPositive_ && !int2.isPositive_){
    return true;
  } else if(!this->isPositive_ && int2.isPositive_){
    return false;
  } else if(this->isPositive_ && int2.isPositive_){
    return firstIsBiggerThanSecond(this->fullInteger_, int2.fullInteger_);
  } else if(!this->isPositive_ && !int2.isPositive_){
    return firstIsBiggerThanSecond(int2.fullInteger_, this->fullInteger_);
  }
  assert(false);
  return true;
}
bool BigInt::operator<(const BigInt &otherInteger) const{
  return otherInteger > (*this);
}
bool BigInt::operator>=(const BigInt &otherInteger) const{
  return !((*this) < otherInteger);
}
bool BigInt::operator<=(const BigInt &otherInteger) const{
  return !((*this) > otherInteger);
}




//TODO change this implementation so that the first does not have to be bigger than the second one.

vector<ull> BigInt::difference(vector<ull> num1, const vector<ull> &num2) const{
  assert(firstIsBiggerThanSecond(num1, num2) || num1 == num2);
  vector<ull> result;
  int i;
  for(i = 0; i < num2.size(); ++i){
    if(num1[i] >= num2[i]){
      result.push_back(num1[i] - num2[i]);
    } else{
      /*
       * Guaranteed no overflow because num2[i]>num1[i]
       */
      result.push_back(std::numeric_limits<ull>::max() - num2[i] + 1 + num1[i]);
      auto temp = i + 1;
      while(num1[temp] == 0){
        num1[temp] = std::numeric_limits<ull>::max();
        ++temp;
      }
      /*
       * This is only okay because num1>num2
       */
      --num1[temp];
    }
  }

  //Add what is remaining of the bigger number.
  int max = num1.size() - 1;
  while(num1[max] == 0ULL){
    --max;
  }
  while(i <= max){
    result.push_back(num1[i]);
    ++i;
  }

  //Removing trailing zeros of the result
  i = result.size() - 1;
  while(result[i] == 0){
    result.pop_back();
    --i;
  }
  return result;
}
vector<ull> BigInt::add(const vector<ull> &num1, const vector<ull> &num2) const{
  vector<ull> sum;
  int i;
  bool carryOne = false;
  const auto &smallerNumberSize = (num1.size() > num2.size()) ? num2.size() : num1.size();
  for(i = 0; i < smallerNumberSize; ++i){
    const ull &n1 = num1[i];
    const ull &n2 = num2[i];
    const ull &remainder = std::numeric_limits<ull>::max() - n2;

    sum.push_back(n1 + n2 + carryOne);

    /*
     * overflow (carry) is detected if
     * 1- n1 is larger than the difference between n2 and max<ull>
     * 2- otherwise, there is overflow if the difference is the same as n1 and there is a previous carry.
     */
    if(n1 > remainder || (n1 == remainder && carryOne)){
      carryOne = true;
    } else{
      carryOne = false;
    }
  }

  const auto &biggerNumber = (num1.size() > num2.size()) ? num1 : num2;

  if(carryOne){
    while(i < biggerNumber.size() && biggerNumber[i] == std::numeric_limits<ull>::max()){
      sum.push_back(0);
      ++i;
    }
    if(i == biggerNumber.size()){
      sum.push_back(1);
    } else{
      sum.push_back(biggerNumber[i] + 1);
      ++i;
    }
  }
  while(i < biggerNumber.size()){
    sum.push_back(biggerNumber[i]);
    ++i;
  }
  return sum;
}

BigInt &BigInt::operator+=(const BigInt &NumberToAdd){
  if(this->isPositive_ == NumberToAdd.isPositive_){
    fullInteger_ = add(fullInteger_, NumberToAdd.fullInteger_);
  } else{
    if(fullInteger_ == NumberToAdd.fullInteger_){
      fullInteger_ = {0};
      this->isPositive_ = true;
      return *this;
    }
    const bool &thisNumberIsBigger = firstIsBiggerThanSecond(fullInteger_, NumberToAdd.fullInteger_);
    const BigInt &biggerNumber = thisNumberIsBigger ? *this : NumberToAdd;
    const BigInt &smallerNumber = thisNumberIsBigger ? NumberToAdd : *this;
    this->fullInteger_ = difference(biggerNumber.fullInteger_, smallerNumber.fullInteger_);
    if(!thisNumberIsBigger){
      this->isPositive_ = !this->isPositive_;
    }
  }
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &numberToSubtract){
  if(this->isPositive_ != numberToSubtract.isPositive_){
    this->fullInteger_ = add(fullInteger_, numberToSubtract.fullInteger_);
  } else{
    if(fullInteger_ == numberToSubtract.fullInteger_){
      fullInteger_ = {0};
      this->isPositive_ = true;
      return *this;
    }
    const bool &thisIsBigger = firstIsBiggerThanSecond(fullInteger_, numberToSubtract.fullInteger_);
    const BigInt &biggerNumber = thisIsBigger ? *this : numberToSubtract;
    const BigInt &smallerNumber = thisIsBigger ? numberToSubtract : *this;
    this->fullInteger_ = difference(biggerNumber.fullInteger_, smallerNumber.fullInteger_);
    if(!thisIsBigger){
      this->isPositive_ = !this->isPositive_;
    }
  }
  return *this;
}


BigInt operator+(BigInt lhs, const BigInt &rhs){
  lhs += rhs; // reuse compound assignment
  return lhs; // return the result by value (uses move constructor)
}
BigInt operator-(BigInt lhs, const BigInt &rhs){
  lhs -= rhs;
  return lhs;
}
BigInt &BigInt::operator++(){
  (*this) += 1;
  return *this;
}
BigInt BigInt::operator++(int){
  BigInt tmp(*this);
  (*this) += 1;
  return tmp;
}


BigInt &BigInt::operator--(){
  (*this) -= 1;
  return *this;
}
BigInt BigInt::operator--(int){
  BigInt tmp(*this);
  (*this) -= 1;
  return tmp;
}


//Using the double dabble algorithm, based on Wikipedia C code
//TODO this needs major optimization for large numbers.
std::string BigInt::toString() const{
  assert(!fullInteger_.empty());
  if(fullInteger_.size() == 1){
    if(isPositive_){
      return std::to_string(fullInteger_[0]);
    } else{
      return std::string("-") + std::to_string(fullInteger_[0]);
    }
  }
  std::vector<char> result(1);
  int bitToShift = 0;
  for(int i = fullInteger_.size() - 1; i >= 0; --i){
    for(int j = sizeof(ull) * 8 - 1; j >= 0; --j){
      if((fullInteger_[i] & (1ULL << j)) > 0){
        bitToShift = 1;
      } else{
        bitToShift = 0;
      }
      for(int k = 0; k < result.size(); ++k){
        if(result[k] >= 5){
          result[k] += 3;
        }
      }
      if(result[result.size() - 1] >= 8){
        result.push_back(0);
      }
      for(int k = result.size() - 1; k > 0; --k){
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
  while(result[last] == 0){
    --last;
  }

  for(int i = last; i >= 0; --i){
    result[i] += '0';
  }
  if(isPositive_){
    return std::string(result.rbegin(), result.rend());
  } else{
    return std::string("-") + std::string(result.rbegin(), result.rend());
  }
}

bool BigInt::operator==(const BigInt &int2) const{
  if(this->isPositive_ != int2.isPositive_){
    return false;
  }
  if(this->fullInteger_.size() != int2.fullInteger_.size()){
    return false;
  }
  for(int i = 0; i < this->fullInteger_.size(); ++i){
    if(this->fullInteger_[i] != int2.fullInteger_[i]){
      return false;
    }
  }
  return true;
}
bool BigInt::operator!=(const BigInt &int2) const{
  return !((*this) == int2);
}
string BigInt::divByTwo(const string &s){
  if(s == "0" || s == "1"){
    return "0";
  }
  string newString("");
  int toAdd = 0;
  for(const char &ch:s){
    if(!std::isdigit(ch)){
      cout << "ERROR: " << s << " is not a numer." << endl;
      exit(0);
    }
    newString += std::to_string((toDigit(ch) / 2 + toAdd));
    toAdd = ((int) ch) % 2 == 1 ? 5 : 0;
  }
  if(newString[0] == '0'){
    newString.erase(0, 1);
  }
  return newString;
}
string BigInt::convertToBinary(string num){
  if(num == "0"){
    return string("0");
  }
  string result("");
  while(num != "0"){
    result += string((int) num[num.size() - 1] % 2 == 1 ? "1" : "0");
    num = divByTwo(num);
  }
  return string(result.rbegin(), result.rend());
}
ull BigInt::stringToUll(const string s){
  ull result = 0ULL;
  for(int i = 0; i < s.size(); ++i){
    assert(s[i] == '1' || s[i] == '0');
    result <<= 1;
    if(s[i] == '1'){
      result |= 1;
    }
  }
  return result;
}


BigInt &BigInt::operator<<=(BigInt shiftBy){
  assert(shiftBy.isPositive_);
  static BigInt zero;
  if(shiftBy.fullInteger_.empty() || fullInteger_.empty() || (*this) == zero || shiftBy == zero){
    return (*this);
  }
  static const BigInt maxShift(64);
  while(shiftBy >= maxShift){
    shiftBy -= maxShift;
    fullInteger_.insert(fullInteger_.begin(), 0);
  }
  if(shiftBy == zero){
    return (*this);
  }
  const ull &finalShiftAmount = shiftBy.fullInteger_[0];
  const ull &shiftMask = std::numeric_limits<ull>::max() << (64ULL - finalShiftAmount);

  if((fullInteger_[fullInteger_.size() - 1] & shiftMask) > 0ULL){
    fullInteger_.push_back(0);
  }
  for(int i = fullInteger_.size() - 1; i > 0; --i){
    fullInteger_[i] <<= finalShiftAmount;
    fullInteger_[i] |= ((fullInteger_[i - 1] & shiftMask) >> (64ULL - finalShiftAmount));
  }
  fullInteger_[0] <<= finalShiftAmount;
  return (*this);
}

/*
Bitshifiting to the right by a given amount.
Param shiftBy has to be positive
*/
BigInt &BigInt::operator>>=(BigInt shiftBy){
  assert(shiftBy.isPositive_);
  static BigInt zero;
  if(shiftBy.fullInteger_.empty() || fullInteger_.empty() || (*this) == zero || shiftBy == zero){
    return (*this);
  }
  static BigInt maxShift(64);
  while(shiftBy >= maxShift){
    shiftBy -= maxShift;
    fullInteger_.erase(fullInteger_.begin());
    if(fullInteger_.empty()){
      fullInteger_.push_back(0);
      return (*this);
    }
  }
  if(shiftBy == zero){
    return (*this);
  }
  const ull &finalShiftAmount = shiftBy.fullInteger_[0];
  const ull &shiftMask = std::numeric_limits<ull>::max() >> (64ULL - finalShiftAmount);
  for(int i = 0; i < fullInteger_.size() - 1; ++i){
    fullInteger_[i] >>= finalShiftAmount;
    fullInteger_[i] |= ((fullInteger_[i + 1] & shiftMask) << (64LL - finalShiftAmount));
  }
  fullInteger_[fullInteger_.size() - 1] >>= finalShiftAmount;
  return (*this);
}
BigInt operator>>(BigInt lhs, BigInt shiftBy){
  lhs >>= shiftBy;
  return lhs;
}
BigInt operator<<(BigInt lhs, BigInt shiftBy){
  lhs <<= shiftBy;
  return lhs;
}


}//namespace bigint;