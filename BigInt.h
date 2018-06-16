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
#include <string>

using std::vector;
using std::size_t;
using std::string;
using std::cout;
using std::endl;
typedef unsigned long long ull;
#define toDigit(c) (c-'0')


namespace bigint{
class BigInt{
private:

  //instance variable
  vector<ull> fullInteger_;
  bool isPositive_ = true;


  string divByTwo(const string &s);
  string convertToBinary(string num);

  ull stringToUll(const string s);


public:

  inline vector<ull> fullInteger() const {
    return fullInteger_;
  }
  inline bool isPositive() const {
    return isPositive_;
  }
  //constructors
  inline BigInt(const string &s) {
    if(s.empty()) {
      fullInteger_.push_back(0);
      return;
    }
    string bin;
    switch(s[0]) {
      case '-':
        isPositive_ = false;
      case '+':
        bin = convertToBinary(string(s.begin() + 1, s.end()));
        break;
      default:
        bin = convertToBinary(s);
    }

    int i;
    for(i = bin.size(); i - (int) (sizeof(ull) * 8) >= 0; i -= (sizeof(ull) * 8)) {
      fullInteger_.push_back(stringToUll(string(bin.begin() + (i - sizeof(ull) * 8), bin.begin() + i)));
    }
    if(i != 0) {
      fullInteger_.push_back(stringToUll(string(bin.begin(), bin.begin() + i)));
    }

    //Removing padding zeros
    for(int i = fullInteger_.size() - 1; i > 0; --i) {
      if(fullInteger_[i] == 0) {
        fullInteger_.pop_back();
      } else {
        return;
      }
    }

    //checking if the number is zero
    if(fullInteger_.size() == 1 && fullInteger_[0] == 0) {
      isPositive_ = true;
    }
  }
  //Constructor that takes any numerical type as input.
  template<
      typename T,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  BigInt(T baseInteger) {
    if(baseInteger < ((T) 0)) {
      isPositive_ = false;
      fullInteger_.push_back((ull) (baseInteger * -1));
    } else {
      fullInteger_.push_back(baseInteger);
    }
  }

  BigInt(const BigInt &baseInteger) : fullInteger_(baseInteger.fullInteger_), isPositive_(baseInteger.isPositive_) {};
  BigInt(BigInt &&baseInteger) : fullInteger_(std::move(baseInteger.fullInteger_)),
                                 isPositive_(baseInteger.isPositive_) {};
  BigInt() { fullInteger_.push_back(0); }

/*
 * Equality and inequality comparison operators
 */
  friend bool operator==(const BigInt &int1, const BigInt &int2);
  friend bool operator!=(const BigInt &int1, const BigInt &int2) {
    return !(int1 == int2);
  }

//comparison
  bool operator>(const BigInt &int2) const;

  bool operator<(const BigInt &int2) const;
  bool operator>=(const BigInt &int2) const;
  bool operator<=(const BigInt &int2) const;


  void difference(vector<ull> num1, const vector<ull> &num2, vector<ull> &result) const;
  void add(const vector<ull> &num1, const vector<ull> &num2, vector<ull> &result) const;


  //functions
  BigInt &operator+=(const BigInt &toAdd);
  friend BigInt operator+(BigInt lhs, const BigInt &rhs);

  BigInt &operator-=(const BigInt &toSubtract);
  friend BigInt operator-(BigInt lhs, const BigInt &rhs);

  BigInt &operator++();
  BigInt operator++(int);
  BigInt &operator--();
  BigInt operator--(int);

  std::string toString() const;


}; //class BigInt

//template<typename T, typename>
//BigInt::BigInt(T baseInteger) {
//  if(baseInteger < ((T) 0)) {
//    isPositive_ = false;
//    fullInteger_.push_back((ull) (baseInteger * -1));
//  } else {
//    fullInteger_.push_back(baseInteger);
//  }
//}

//To pringt a bigInt object (toString)
inline std::ostream &operator<<(std::ostream &out, BigInt &integer) {
  out << integer.toString();
  return out;
}
}//namespace bigint


#endif //BIGINT2_BIGINT_H
