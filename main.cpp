#include <iostream>
#include <vector>
#include <bitset>

#include "BigInt.h"

using std::vector;
using std::cout;
using std::endl;
typedef unsigned long long ull;

int main() {
  std::cout << "Hello, World!" << std::endl;
  ull integer = 52324324623;
  bigint::BigInt int1(integer);
  int1.fullInteger_[0]=21;
  int1.fullInteger_.push_back(21);
  int1.fullInteger_.push_back(21);
  cout << int1 << endl;
  cout<<integer<<endl;


  return 0;
}