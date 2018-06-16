//
// Created by Yaser Alkayale on 2018-06-08.
//

#include "catch.hpp"
#include "../BigInt.h"

using bigint::BigInt;
using std::vector;


void checkAllOperatorsFirstBiggerThanSecond(const BigInt &num1, const BigInt &num2) {
  REQUIRE_FALSE(num1 == num2);
  REQUIRE_FALSE(num2 == num1);
  REQUIRE(num1 != num2);
  REQUIRE(num2 != num1);
  REQUIRE(num1 >= num2);
  REQUIRE_FALSE(num2 >= num1);
  REQUIRE_FALSE(num1 <= num2);
  REQUIRE(num2 <= num1);
  REQUIRE(num2 < num1);
  REQUIRE_FALSE(num1 < num2);
  REQUIRE(num1 > num2);
  REQUIRE_FALSE(num2 > num1);
}

void checkAllOperatorsEqual(const BigInt &num1, const BigInt &num2) {
  REQUIRE(num1 == num2);
  REQUIRE(num2 == num1);
  REQUIRE_FALSE(num1 != num2);
  REQUIRE_FALSE(num2 != num1);
  REQUIRE(num1 >= num2);
  REQUIRE(num2 >= num1);
  REQUIRE(num1 <= num2);
  REQUIRE(num2 <= num1);
  REQUIRE_FALSE(num2 < num1);
  REQUIRE_FALSE(num1 < num2);
  REQUIRE_FALSE(num1 > num2);
  REQUIRE_FALSE(num2 > num1);
}

TEST_CASE("Comparison than works for positive and negative numbers.") {
  vector<ull> largeNums1{75, 876324, 752};
  vector<ull> largeNums2{785, 876324, 75232};

  BigInt negative1(-1567);
  BigInt negative1_copy = negative1;
  BigInt negative2(-67234);
  BigInt largeNegative1("-1234788929148347138292");
  BigInt largeNegative2("-8919132423478418929113448347138292");

  BigInt largeNegative3("-1361129467684991793892783810002005524480");
  BigInt largeNegative4("-1361129467684991793892783810002005524496");


  BigInt positive1(123);
  BigInt positive1_copy = positive1;
  BigInt positive2(98625373);

  BigInt zero(0);
  BigInt zero2(0);
  BigInt largePositive1("1234788929148347138292");
  BigInt largePositive2("8919132423478418929113448347138292");
  BigInt largePositive3("1361129467684991793892783810002005524480");
  BigInt largePositive4("1361129467684991793892783810002005524496");

  BigInt largePositiveNumberCopy(largePositive1);
  SECTION("toString works") {
    REQUIRE(zero.toString() == "0");
    REQUIRE(negative1.toString() == "-1567");
    REQUIRE(negative2.toString() == "-67234");
    REQUIRE(BigInt("-3245432").toString() == "-3245432");
    REQUIRE(largeNegative1.toString() == "-1234788929148347138292");
    REQUIRE(largeNegative2.toString() == "-8919132423478418929113448347138292");
    REQUIRE(largeNegative3.toString() == "-1361129467684991793892783810002005524480");

    REQUIRE(positive1.toString() == "123");
    REQUIRE(positive2.toString() == "98625373");
    REQUIRE(largePositive1.toString() == "1234788929148347138292");
    REQUIRE(largePositive2.toString() == "8919132423478418929113448347138292");
    REQUIRE(largePositive3.toString() == "1361129467684991793892783810002005524480");
    REQUIRE(BigInt("3245432").toString() == "3245432");
  }
  SECTION("Negative Number Equality.") {
    checkAllOperatorsEqual(negative1, negative1);
    checkAllOperatorsEqual(negative1, negative1_copy);

  }
  SECTION("Negative large number equality") {
    BigInt largeNegative1_copy(largeNegative1);
    checkAllOperatorsEqual(largeNegative1, largeNegative1_copy);
  }
  SECTION("Negative Number Small Comparison") {
    checkAllOperatorsFirstBiggerThanSecond(negative1, negative2);
  }

  SECTION("Negative Number Large number comparison") {
    checkAllOperatorsFirstBiggerThanSecond(largeNegative1, largeNegative2);
  }
  SECTION("Small negative with large negative comparison") {
    checkAllOperatorsFirstBiggerThanSecond(negative1, largeNegative1);
  }
  SECTION("Zero and large negative") {
    checkAllOperatorsFirstBiggerThanSecond(zero, largeNegative2);
  }
  SECTION("Zero with zero") {
    checkAllOperatorsEqual(zero, zero2);
  }
  SECTION("Zero and positive") {
    checkAllOperatorsFirstBiggerThanSecond(largePositive4, zero);
  }
}

TEST_CASE("Initialization works") {
  BigInt zero1(0);
  BigInt zero2("-0");
  BigInt zero3;

  REQUIRE(zero1 == 0);
  REQUIRE(zero2 == 0);
  REQUIRE(zero3 == 0);

  BigInt one1(1);
  BigInt one2("1");
  BigInt one3("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

  REQUIRE(one1 == 1);
  REQUIRE(one2 == 1);
  REQUIRE(one3 == 1);

  BigInt negativeOne(
      "-000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

  REQUIRE(negativeOne == -1);

  BigInt largePositive("18446744073709551616");




}


TEST_CASE("Addition Works") {

  BigInt positiveSmall1(50);
  BigInt positiveSmall2(100);
  BigInt zero1(0);
  BigInt zero2(0);


  BigInt negativeSmall1(-50);
  BigInt negativeSmall2(-100);
  BigInt max(std::numeric_limits<ull>::max());

  SECTION("Adding two zeros works") {
    REQUIRE((zero1 + zero2) == 0);


  }
  //adds("Adding small positive numbers works". positiveSmall1,positiveSmall2);
  //SECTION(){
  //
  //}

}