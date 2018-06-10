//
// Created by Yaser Alkayale on 2018-06-06.
//

/*
 * Implementation of bigInt for multiple percision integer operations
 *
 * A big integer is defined used a vector of unsigned long longs.
 * The vector at position 0 is the least significant part of the integer, and it goes on from there.
 */

#ifndef BIGINT2_BIGINT_H
#define BIGINT2_BIGINT_H

#include <vector>
#include <iostream>
#include <cassert>

using std::vector;
using std::size_t;
typedef unsigned long long ull;

namespace bigint{
class BigInt{
public:
  //instance variable
  std::vector<ull> fullInteger_;
  bool isPositive_ = true;


  //constructors
  template<
      typename T,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  inline BigInt(T baseInteger);

  inline BigInt(const BigInt &baseInteger) : fullInteger_(baseInteger.fullInteger_),isPositive_(baseInteger.isPositive_) {};
  inline BigInt(BigInt &&baseInteger) : fullInteger_(std::move(baseInteger.fullInteger_)),isPositive_(baseInteger.isPositive_) {};
  BigInt() {}

/*
 * Equality and inequality comparison operators
 */
  friend bool operator==(const BigInt &int1, const BigInt &int2);

  friend bool operator!=(const BigInt &int1, const BigInt &int2);

//comparison
  bool operator>(const BigInt &int2) const;

  bool operator<(const BigInt &int2) const;
  bool operator>=(const BigInt &int2) const;
  bool operator<=(const BigInt &int2) const;



  inline void difference(vector<ull> num1, const vector<ull> &num2, vector<ull> &result) const;
  inline void add(const vector<ull> &num1, const vector<ull> &num2, vector<ull> &result) const {
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


  //functions
  inline BigInt &operator+=(const BigInt &toAdd) {
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
  friend BigInt operator+(BigInt lhs,        // passing lhs by value helps optimize chained a+b+c
                          const BigInt &rhs) // otherwise, both parameters may be const references
  {
    lhs += rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  inline BigInt &operator++() {
    (*this) += 1;
    return *this;
  }
  inline BigInt operator++(int) {
    BigInt tmp(*this);
    (*this) += 1;
    return tmp;
  }

  inline std::string toString() const {
    std::vector<char> result(1);
    int bitToShift = 0;
    for(int i = fullInteger_.size() - 1; i >= 0; --i) {
      for(int j = sizeof(ull) * 8 - 1; j >= 0; --j) {
        if((fullInteger_[i] & ((ull) 1 << j)) > 0) {
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

      };
    }
    int last = result.size();
    while(result[--last] == 0);

    for(int i = last; i >= 0; --i) {
      result[i] += '0';
    }
    return std::string(result.begin(), result.end());
  }


}; //class BigInt



}//namespace bigint


#endif //BIGINT2_BIGINT_H
