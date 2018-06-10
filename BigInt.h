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

  //Constructor that takes any numerical type as input.
  template<
      typename T,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  BigInt(T baseInteger);

  BigInt(const BigInt &baseInteger) : fullInteger_(baseInteger.fullInteger_), isPositive_(baseInteger.isPositive_) {};
  BigInt(BigInt &&baseInteger) : fullInteger_(std::move(baseInteger.fullInteger_)),
                                 isPositive_(baseInteger.isPositive_) {};
  BigInt() {}

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
  friend BigInt operator+(BigInt lhs,        // passing lhs by value helps optimize chained a+b+c
                          const BigInt &rhs);

  BigInt &operator++();
  BigInt operator++(int);
  BigInt &operator--();
  BigInt operator--(int);

  std::string toString() const;


}; //class BigInt

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

//To pringt a bigInt object (toString)
inline std::ostream &operator<<(std::ostream &out, BigInt &integer) {
  out << integer.toString();
  return out;
}
}//namespace bigint


#endif //BIGINT2_BIGINT_H
