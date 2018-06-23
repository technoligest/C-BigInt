//
// Created by Yaser Alkayale on 2018-06-08.
//

#define _DEBUG


#include "catch.hpp"
#include "../lib/BigInt.h"

using bigint::BigInt;
TEST_CASE("Correct initialization of constructor.") {
  SECTION("Null initialization") {
    BigInt int1;
    CHECK(int1.fullInteger() == vector<ull>{0});
    CHECK(int1.isPositive());
  }
  SECTION("Initialization using numbers") {
    BigInt zero1(0);
    CHECK(zero1.fullInteger() == vector<ull>{0});
    CHECK(zero1.isPositive());

    BigInt int1(1234);
    CHECK(int1.fullInteger() == vector<ull>{1234});
    CHECK(int1.isPositive());

    BigInt int2(-1234);
    CHECK(int2.fullInteger() == vector<ull>{1234});
    CHECK_FALSE(int2.isPositive());

    BigInt int5("1234");
  }
  SECTION("copy constructor") {
    BigInt int1(1234);
    BigInt int3(int1);
    CHECK(int3.fullInteger() == vector<ull>{1234});
    CHECK(int3.isPositive());

    BigInt int4(BigInt(5000));
    CHECK(int4.fullInteger() == vector<ull>{5000});
    CHECK(int4.isPositive());
  };

  SECTION("confirming that the constructor is not explicit") {
    BigInt int1 = 243555;
    CHECK(int1.fullInteger() == vector<ull>{243555});
  };

  SECTION("initilization using string constructor") {
    CHECK(BigInt("-0").fullInteger() == vector<ull>{0});
    CHECK(BigInt("-0").isPositive());
    BigInt zero(
        "-0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");


    CHECK(zero.fullInteger() == vector<ull>{0});
    CHECK(zero.isPositive());


    ;

    CHECK(BigInt("1").fullInteger() == vector<ull>{1});
    CHECK(BigInt("1").isPositive());

    BigInt one(
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    CHECK(one.fullInteger() == vector<ull>{1});
    CHECK(one.isPositive());


  }

  SECTION("initialization of large numbers") {
    BigInt negativeOne(
        "-000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

    CHECK(negativeOne == -1);

    BigInt largePositive1("18446744073709551616");

    CHECK(largePositive1.fullInteger() == vector<ull>{0ULL, 1ULL});

    BigInt largePositive2("1234323145243152123441345");
    CHECK(largePositive2.fullInteger() == vector<ull>{14605783098605711553ULL, 66912ULL});

    BigInt largePositive3("78609192494621647456094388351");
    CHECK(largePositive3.fullInteger() == vector<ull>{127ULL, 4261412864ULL});

    BigInt largePositive4(
        "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174");
    CHECK(largePositive4.fullInteger() == vector<ull>{200000000000000182, 1, 0, 0, 0, 0, 0, 4503599627370496});
    CHECK(largePositive4.isPositive());

    BigInt largePositive5(
        "-3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174");
    CHECK(largePositive5.fullInteger() == vector<ull>{200000000000000182, 1, 0, 0, 0, 0, 0, 4503599627370496});
    CHECK_FALSE((largePositive5.isPositive()));
  }


}

TEST_CASE("BigInt is initialized to sign of value given by default") {
  BigInt int1(123432);
  CHECK(int1.isPositive());

  BigInt int2(-1234);
  CHECK_FALSE(int2.isPositive());

  BigInt int3(0);
  CHECK(int3.isPositive());
}

void checkAllOperatorsFirstBiggerThanSecond(const BigInt &num1, const BigInt &num2) {
  CHECK_FALSE(num1 == num2);
  CHECK_FALSE(num2 == num1);
  CHECK(num1 != num2);
  CHECK(num2 != num1);
  CHECK(num1 >= num2);
  CHECK_FALSE(num2 >= num1);
  CHECK_FALSE(num1 <= num2);
  CHECK(num2 <= num1);
  CHECK(num2 < num1);
  CHECK_FALSE(num1 < num2);
  CHECK(num1 > num2);
  CHECK_FALSE(num2 > num1);
}

void checkAllOperatorsEqual(const BigInt &num1, const BigInt &num2) {
  CHECK(num1 == num2);
  CHECK(num2 == num1);
  CHECK_FALSE(num1 != num2);
  CHECK_FALSE(num2 != num1);
  CHECK(num1 >= num2);
  CHECK(num2 >= num1);
  CHECK(num1 <= num2);
  CHECK(num2 <= num1);
  CHECK_FALSE(num2 < num1);
  CHECK_FALSE(num1 < num2);
  CHECK_FALSE(num1 > num2);
  CHECK_FALSE(num2 > num1);
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
    CHECK(zero.toString() == "0");
    CHECK(negative1.toString() == "-1567");
    CHECK(negative2.toString() == "-67234");
    CHECK(BigInt("-3245432").toString() == "-3245432");
    CHECK(largeNegative1.toString() == "-1234788929148347138292");
    CHECK(largeNegative2.toString() == "-8919132423478418929113448347138292");
    CHECK(largeNegative3.toString() == "-1361129467684991793892783810002005524480");

    CHECK(positive1.toString() == "123");
    CHECK(positive2.toString() == "98625373");
    CHECK(largePositive1.toString() == "1234788929148347138292");
    CHECK(largePositive2.toString() == "8919132423478418929113448347138292");
    CHECK(largePositive3.toString() == "1361129467684991793892783810002005524480");
    CHECK(BigInt("3245432").toString() == "3245432");
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

bool checkAddition(BigInt int1, BigInt int2, BigInt result) {

  CHECK(int1 + int2 == result);
  CHECK(int2 + int1 == result);

  auto int1Copy = int1;
  auto int2Copy = int2;

  int1Copy += int2;
  int2Copy += int1;
  CHECK(int1Copy == result);
  CHECK(int2Copy == result);

  return true;
}

TEST_CASE("Addition Works") {

  BigInt zero;
  BigInt zero1(0);
  BigInt zero2("-0");

  BigInt positiveSmall1(50);
  BigInt negativeSmall1(-50);

  BigInt positiveSmall2(100);
  BigInt negativeSmall2(-100);

  BigInt positiveOverflow1(9223372036854775899ULL);
  BigInt negativeOverflow1("-9223372036854775899");

  BigInt positiveOverflow2(9423372036854775899ULL);
  BigInt negativeOverflow2("-9423372036854775899");

  BigInt positiveMax("+18446744073709551615"); //std::numeric_limits<ull>::max()
  BigInt negativeMax("-18446744073709551615");

  BigInt negativeLarge1("-136112946768499179389278381000553455432005524480");
  BigInt positiveLarge1("+136112946768499179389278381000553455432005524480");


  //9223372036854775899 + 2^500
  BigInt positiveOverflow3(

      "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545894616425365382365275");
  BigInt negativeOverflow3(
      "-3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545894616425365382365275");

  SECTION("Adding zeros") {
    checkAddition(zero, zero2, BigInt(0));
    checkAddition(zero, positiveSmall1, positiveSmall1);
    checkAddition(zero, negativeSmall1, negativeSmall1);
    checkAddition(zero, positiveOverflow3, positiveOverflow3);
    checkAddition(zero, negativeLarge1, negativeLarge1);
  }

  SECTION("Adding small positive integers without overflow works.") {
    checkAddition(positiveSmall1, positiveSmall2, 150);
  }
  SECTION("Adding small positive integers with overflow.") {
    checkAddition(positiveOverflow1, positiveOverflow2, BigInt("18646744073709551798"));
  }
  SECTION("Adding largepositive integers without overflow") {
    checkAddition(positiveOverflow3, positiveOverflow2, BigInt(
        "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545904039797402237141174"));
  }
  SECTION("Adding positive and negative numbers;") {
    checkAddition(positiveSmall1, negativeSmall1, 0);
    checkAddition(positiveMax, negativeOverflow1, 9223372036854775716);
    checkAddition(positiveOverflow3, negativeLarge1, BigInt("3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150750571180791571829827978164894062969933376840795"));
    checkAddition(positiveOverflow1,negativeOverflow2,BigInt("-200000000000000000"));
    checkAddition(positiveOverflow3, negativeLarge1,BigInt("3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150750571180791571829827978164894062969933376840795"));
  }

}

bool checkSubtraction(BigInt int1, BigInt int2, BigInt result) {
  CHECK(int1 - int2 == result);
  auto int1Copy = int1;
  int1Copy -= int2;
  CHECK(int1Copy == result);


  auto res = int2 - int1;
  auto int2Copy = int2;
  int2Copy -= int1;

  CHECK(res.fullInteger() == result.fullInteger());
  CHECK(int2Copy.fullInteger() == result.fullInteger());
  if(result != 0) {
    CHECK(res.isPositive() != result.isPositive());
    CHECK(int2Copy.isPositive() != result.isPositive());
  } else {
    CHECK(res.isPositive());
    CHECK(int2Copy.isPositive());
  }
  return true;
}

TEST_CASE("Subtraction.") {

  BigInt zero;
  BigInt zero1(0);
  BigInt zero2("-0");

  BigInt positiveSmall1(50);
  BigInt negativeSmall1(-50);

  BigInt positiveSmall2(100);
  BigInt negativeSmall2(-100);

  BigInt positiveOverflow1(9223372036854775899ULL);
  BigInt negativeOverflow1("-9223372036854775899");

  BigInt positiveOverflow2(9423372036854775899ULL);
  BigInt negativeOverflow2("-9423372036854775899");

  BigInt positiveMax("+18446744073709551615"); //std::numeric_limits<ull>::max()
  BigInt negativeMax("-18446744073709551615");

  BigInt negativeLarge1("-136112946768499179389278381000553455432005524480");
  BigInt positiveLarge1("+136112946768499179389278381000553455432005524480");


  //9223372036854775899 + 2^500
  BigInt positiveOverflow3(
      "3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545894616425365382365275");
  BigInt negativeOverflow3(
      "-3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545894616425365382365275");


  SECTION("Subtracting zeros works") {
    checkSubtraction(zero2, zero, zero);
    checkSubtraction(positiveSmall1, zero, positiveSmall1);
    checkSubtraction(negativeSmall1, zero, negativeSmall1);
    checkSubtraction(positiveOverflow3, zero, positiveOverflow3);
    checkSubtraction(negativeLarge1, zero, negativeLarge1);
  }

  SECTION("positive numbers first is larger.") {
    //cout<<negativeLarge1.fullInteger()[123]<<endl;
  }
}