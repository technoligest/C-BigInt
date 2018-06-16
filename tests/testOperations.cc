//
// Created by Yaser Alkayale on 2018-06-08.
//

#include "catch.hpp"
#include "../BigInt.h"

using bigint::BigInt;
using std::vector;
TEST_CASE("Correct initialization of constructor.") {
  SECTION("Null initialization") {
    BigInt int1;
    REQUIRE(int1.fullInteger() == vector<ull>{0});
    REQUIRE(int1.isPositive());
  }
  SECTION("Initialization using numbers") {
    BigInt zero1(0);
    REQUIRE(zero1.fullInteger() == vector<ull>{0});
    REQUIRE(zero1.isPositive());

    BigInt int1(1234);
    REQUIRE(int1.fullInteger() == vector<ull>{1234});
    REQUIRE(int1.isPositive());

    BigInt int2(-1234);
    REQUIRE(int2.fullInteger() == vector<ull>{1234});
    REQUIRE_FALSE(int2.isPositive());

    BigInt int5("1234");
  }
  SECTION("copy constructor") {
    BigInt int1(1234);
    BigInt int3(int1);
    REQUIRE(int3.fullInteger() == vector<ull>{1234});
    REQUIRE(int3.isPositive());

    BigInt int4(BigInt(5000));
    REQUIRE(int4.fullInteger() == vector<ull>{5000});
    REQUIRE(int4.isPositive());
  };

  SECTION("confirming that the constructor is not explicit") {
    BigInt int1 = 243555;
    REQUIRE(int1.fullInteger() == vector<ull>{243555});
  };

  SECTION("initilization using string constructor") {
    REQUIRE(BigInt("-0").fullInteger() == vector<ull>{0});
    REQUIRE(BigInt("-0").isPositive());
    BigInt zero(
        "-0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");


    REQUIRE(zero.fullInteger() == vector<ull>{0});
    REQUIRE(zero.isPositive());


    ;

    REQUIRE(BigInt("1").fullInteger() == vector<ull>{1});
    REQUIRE(BigInt("1").isPositive());

    BigInt one(
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    REQUIRE(one.fullInteger() == vector<ull>{1});
    REQUIRE(one.isPositive());


  }

  SECTION("initialization of large numbers") {
    BigInt negativeOne(
        "-000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

    REQUIRE(negativeOne == -1);

    BigInt largePositive1("18446744073709551616");

    REQUIRE(largePositive1.fullInteger() == vector<ull>{0ULL, 1ULL});

    BigInt largePositive2("1234323145243152123441345");
    REQUIRE(largePositive2.fullInteger() == vector<ull>{14605783098605711553ULL, 66912ULL});

    BigInt largePositive3("78609192494621647456094388351");
    REQUIRE(largePositive3.fullInteger() == vector<ull>{127ULL, 4261412864ULL});

    BigInt largePositive4(
        "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174");
    REQUIRE(largePositive4.fullInteger() == vector<ull>{200000000000000182, 1, 0, 0, 0, 0, 0, 4503599627370496});
    REQUIRE(largePositive4.isPositive());

    BigInt largePositive5(
        "-3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174");
    REQUIRE(largePositive5.fullInteger() == vector<ull>{200000000000000182, 1, 0, 0, 0, 0, 0, 4503599627370496});
    REQUIRE_FALSE((largePositive5.isPositive()));
  }


}

TEST_CASE("BigInt is initialized to sign of value given by default") {
  BigInt int1(123432);
  REQUIRE(int1.isPositive());

  BigInt int2(-1234);
  REQUIRE_FALSE(int2.isPositive());

  BigInt int3(0);
  REQUIRE(int3.isPositive());
}

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


TEST_CASE("Addition Works") {

  BigInt positiveSmall1(50);
  BigInt positiveSmall2(100);

  BigInt positiveOverflow1(9223372036854775899ULL);
  BigInt positiveOverflow2(9423372036854775899ULL);


  //9223372036854775899 + 2^500
  BigInt positiveOverflow3(
      "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545894616425365382365275");

  BigInt zero1(0);
  BigInt zero2(0);


  BigInt negativeSmall1(-50);
  BigInt negativeSmall2(-100);
  BigInt max(std::numeric_limits<ull>::max());

  SECTION("Adding zeros") {
    REQUIRE((zero1 + zero2) == 0);
    REQUIRE(zero1 + positiveSmall1 == positiveSmall1);
    REQUIRE(positiveSmall1 + zero1 == positiveSmall1);
  }

  SECTION("Adding small positive integers  without overflow works.") {
    REQUIRE(positiveSmall1 + positiveSmall2 == 150);
  }
  SECTION("Adding small positive integers with overflow.") {
    REQUIRE(positiveOverflow1 + positiveOverflow2 == BigInt("18646744073709551798"));
  }
  SECTION("Adding largepositive inteers without overflow") {
    REQUIRE(positiveOverflow3 + positiveOverflow2 == BigInt(
        "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174"));
  }

}