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


using std::vector;
using std::size_t;
typedef unsigned long long ull;
//unsigned long long std::numeric_limits<ull>::max() = std::numeric_limits<ull>::max();
namespace bigint{
class BigInt{
public:
  //instance variable
  std::vector<ull> fullInteger_;
  bool isPositive_ = true;


  //constructors
  template<
      typename T, //real type
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  inline explicit BigInt(T baseInteger) {
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
  inline BigInt(const BigInt &baseInteger) : fullInteger_(baseInteger.fullInteger_) {};
  inline BigInt(BigInt &&baseInteger) : fullInteger_(std::move(baseInteger.fullInteger_)) {};


  explicit BigInt() {}


  //functions
  inline BigInt &operator--() {
    if(fullInteger_.empty()) {
      fullInteger_.push_back(1);
      isPositive_ = false;
      return *this;
    }

    for(size_t i = 0; i < fullInteger_.size(); ++i) {
      --fullInteger_[i];
      if(fullInteger_[i] != std::numeric_limits<ull>::max()) {
        break;
      }
    }

    return *this;
  }
  inline BigInt &operator++() {
    if(fullInteger_.empty()) {
      fullInteger_.push_back(1);
      return *this;
    }
    for(size_t i = 0; i < fullInteger_.size(); ++i) {
      ++fullInteger_[i];
      if(fullInteger_[i] != 0) {
        break;
      }
    }
    if(fullInteger_[fullInteger_.size() - 1] == 0) {
      fullInteger_.push_back(1);
    }
    return *this;
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

};

using std::cout;
using std::endl;

#include <bitset>


inline std::ostream &operator<<(std::ostream &out, BigInt &integer) {
  out << integer.toString();

  return out;
}


/*
 * Equality and inequality comparison operators
 */
inline bool operator==(const BigInt &int1, const BigInt &int2) {
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
inline bool operator==(const BigInt &int1, BigInt &&int2) {
  BigInt int3(int2);
  return int1 == int3;
}
inline bool operator==(BigInt &&int1, const BigInt &int2) {
  BigInt int3(int1);
  return int1 == int2;
}
inline bool operator==(BigInt &&int1, BigInt &&int2) {
  BigInt int3(int1);
  BigInt int4(int2);
  return int3 == int4;
}


inline bool operator!=(const BigInt &int1, const BigInt &int2) {
  return !(int1 == int2);
}
inline bool operator!=(BigInt &&int1, const BigInt &int2) {
  return !(int1 == int2);
}
inline bool operator!=(const BigInt &int1, BigInt &&int2) {
  return !(int1 == int2);
}
inline bool operator!=(BigInt &&int1, BigInt &&int2) {
  return !(int1 == int2);
}

inline BigInt operator-(const BigInt &int1, const BigInt &int2) {
  return BigInt(0);
}


inline BigInt operator+(const BigInt &int1, const BigInt &int2) {
  if(int1.isPositive_ && !int2.isPositive_) {
    BigInt temp(int2);
    temp.isPositive_ = true;
    return int1 - temp;
  } else if(!int1.isPositive_ && int2.isPositive_) {
    BigInt temp(int1);
    return int2 - temp;
  }

  bigint::BigInt result;
  int i = 0;
  int carry = 0;
  while(i < int1.fullInteger_.size() && i < int2.fullInteger_.size()) {
    int num1 = int1.fullInteger_[i];
    int num2 = int2.fullInteger_[i];

    result.fullInteger_.push_back(num1 + num2 + carry);

    if(num1 > std::numeric_limits<ull>::max() - num2 ||
       (carry == 1 && num1 == std::numeric_limits<ull>::max() - num2)) {
      carry = 1;
    } else {
      carry = 0;
    }
    ++i;
  }
  while(i < int1.fullInteger_.size()) {
    result.fullInteger_.push_back(int1.fullInteger_[i]);
    ++i;
  }
  while(i < int2.fullInteger_.size()) {
    result.fullInteger_.push_back(int2.fullInteger_[i]);
  }
  if(!int1.isPositive_ && !int2.isPositive_) {
    result.isPositive_ = false;
  }
  return std::move(result);
}


}//namespace bigint


#endif //BIGINT2_BIGINT_H
