//
// Created by Yaser Alkayale on 2018-06-08.
//

#include "catch.hpp"
#include "../BigInt.h"

using bigint::BigInt;
using std::vector;
//typedef unsigned long long ull;



TEST_CASE("Correct initialization of constructor.") {
  BigInt int1(1234);
  REQUIRE(int1.fullInteger_.size() == 1);
  REQUIRE(int1.fullInteger_[0] == 1234);

  BigInt int2(-1234);
  REQUIRE(int2.fullInteger_.size() == 1);
  REQUIRE(int2.fullInteger_[0] == 1234);

  BigInt int3(int1);
  REQUIRE(int3.fullInteger_.size() == 1);
  REQUIRE(int3.fullInteger_[0] == 1234);
  REQUIRE(int3.isPositive_);

  BigInt int4(BigInt(5000));
  REQUIRE(int4.fullInteger_.size() == 1);
  REQUIRE(int4.fullInteger_[0] == 5000);
  REQUIRE(int4.isPositive_);


  vector<ull> ints;
  int4.fullInteger_ = ints;

  BigInt int5(int4);
  REQUIRE(int5.fullInteger_ == ints);

}

TEST_CASE("BigInt is initialized to sign of value given by default") {
  BigInt int1(123432);
  REQUIRE(int1.isPositive_);

  BigInt int2(-1234);
  REQUIRE_FALSE(int2.isPositive_);

  BigInt int3(0);
  REQUIRE(int3.isPositive_);
}

TEST_CASE("Comparison works for same size positive integers.") {
  BigInt int1(std::numeric_limits<ull>::max());
  BigInt int2(std::numeric_limits<ull>::max());
  assert(int1.isPositive_);
  assert(int1.fullInteger_[0] == std::numeric_limits<ull>::max());
  assert(int2.isPositive_);
  assert(int2.fullInteger_[0] == std::numeric_limits<ull>::max());

  REQUIRE(int1 == int2);
  REQUIRE_FALSE(int2 != int2);

  BigInt int3(0);
  BigInt int4(0);
  REQUIRE(int3 == int4);
  REQUIRE_FALSE(int2 != int2);

  BigInt int5;
  assert(int5.isPositive_);
  vector<ull> ints{499, 123, 123, 900};
  int5.fullInteger_ = ints;

  BigInt int6;
  assert(int6.isPositive_);
  int6.fullInteger_ = ints;

  REQUIRE(int5 == int6);
  REQUIRE_FALSE(int5 != int6);
}

TEST_CASE("Comparison works for same size negative integers.") {
  BigInt int1(std::numeric_limits<ull>::max());
  int1.isPositive_ = false;
  BigInt int2(std::numeric_limits<ull>::max());
  int2.isPositive_ = false;

  REQUIRE(int1 == int2);
  REQUIRE_FALSE(int2 != int2);

  BigInt int3(0);
  BigInt int4(0);
  int3.isPositive_ = false;
  int4.isPositive_ = false;


  REQUIRE(int3 == int4);
  REQUIRE_FALSE(int2 != int2);

  BigInt int5;
  vector<ull> ints{499, 123, 123, 900};
  int5.fullInteger_ = ints;
  int5.isPositive_ = false;

  BigInt int6;
  int6.fullInteger_ = ints;
  int6.isPositive_ = false;

  REQUIRE(int5 == int6);
  REQUIRE_FALSE(int5 != int6);
}
TEST_CASE("Comparison works for same value different sign numbers.") {
  BigInt int1(4);
  BigInt int2(-4);
  REQUIRE(int1 != int2);
  REQUIRE_FALSE(int1 == int2);

  BigInt int3(0);
  BigInt int4(0);
  int4.isPositive_ = false;
  REQUIRE_FALSE(int4.isPositive_);
  REQUIRE_FALSE(int3 != int4);
  REQUIRE(int3 == int4);

}
TEST_CASE("Comparison works for different size positive integers.") {
  BigInt int1(std::numeric_limits<ull>::max());
  BigInt int2(0);
  REQUIRE_FALSE(int1 == int2);
  REQUIRE(int1 != int2);
}
TEST_CASE("Comparison works for rvalues") {
  BigInt int1(std::numeric_limits<ull>::max());
  REQUIRE_FALSE(int1 == BigInt(9));
  REQUIRE(int1 != BigInt(9));
  REQUIRE_FALSE(BigInt(9) == int1);
  REQUIRE(BigInt(9) != int1);

  REQUIRE_FALSE(BigInt(9) == BigInt(99234));
  REQUIRE(BigInt(9) != BigInt(9231));
}

TEST_CASE("Comparison than works for positive and negative numbers.") {
  vector<ull> largeNums1{75, 876324, 752};
  vector<ull> largeNums2{785, 876324, 75232};

  BigInt negative1(-1567);
  BigInt negative1_copy = negative1;
  BigInt negative2(-67234);
  BigInt largeNegative1;
  largeNegative1.isPositive_ = false;
  largeNegative1.fullInteger_ = largeNums1;
  BigInt largeNegative2;
  largeNegative2.isPositive_ = false;
  largeNegative2.fullInteger_ = largeNums2;


  BigInt positive1(123);
  BigInt positive1_copy = positive1;
  BigInt positive2(98625373);

  BigInt zero(0);
  BigInt largePositiveNumber;

  largePositiveNumber.fullInteger_ = largeNums1;
  BigInt largePositiveNumberCopy(largePositiveNumber);


  SECTION("Negative number comparisons.") {
    REQUIRE(negative1 == negative1_copy);
    REQUIRE(negative1_copy == negative1);
    REQUIRE_FALSE(negative1 != negative1_copy);
    REQUIRE_FALSE(negative1_copy != negative1);
    REQUIRE(negative1 >= negative1_copy);
    REQUIRE(negative1_copy >= negative1);
    REQUIRE(negative1 <= negative1_copy);
    REQUIRE(negative1_copy <= negative1);
    REQUIRE_FALSE(negative1 < negative1_copy);
    REQUIRE_FALSE(negative1_copy < negative1);
    REQUIRE_FALSE(negative1 > negative1_copy);
    REQUIRE_FALSE(negative1_copy > negative1);


    REQUIRE_FALSE(negative1 == negative2);
    REQUIRE_FALSE(negative2 == negative1);
    REQUIRE(negative1 != negative2);
    REQUIRE(negative2 != negative1);
    REQUIRE(negative1 >= negative2);
    REQUIRE_FALSE(negative2 >= negative1);
    REQUIRE_FALSE(negative1 <= negative2);
    REQUIRE(negative2 <= negative1);
    REQUIRE(negative2 < negative1);
    REQUIRE_FALSE(negative1 < negative2);
    REQUIRE(negative1 > negative2);
    REQUIRE_FALSE(negative2 > negative1);

    REQUIRE_FALSE(largeNegative1 == largeNegative2);
    REQUIRE_FALSE(largeNegative2 == largeNegative1);
    REQUIRE(largeNegative1 != largeNegative2);
    REQUIRE(largeNegative2 != largeNegative1);
    REQUIRE(largeNegative1 >= largeNegative2);
    REQUIRE_FALSE(largeNegative2 >= largeNegative1);
    REQUIRE_FALSE(largeNegative1 <= largeNegative2);
    REQUIRE(largeNegative2 <= largeNegative1);
    REQUIRE(largeNegative2 < largeNegative1);
    REQUIRE_FALSE(largeNegative1 < largeNegative2);
    REQUIRE(largeNegative1 > largeNegative2);
    REQUIRE_FALSE(largeNegative2 > largeNegative1);
  }


  //REQUIRE(int2 > int1);
  //REQUIRE(int2 >= int1);
  //REQUIRE(int1 < int2);
  //REQUIRE(int1 <= int2);
  //REQUIRE_FALSE(int1 > int2);
  //REQUIRE_FALSE(int1 >= int2);
  //REQUIRE_FALSE(int2 < int1);
  //REQUIRE_FALSE(int2 <= int1);

}