#include <iostream>
#include <vector>
#include <bitset>

#include "BigInt.h"

using std::vector;
using std::cout;
using std::endl;
using bigint::BigInt;
typedef unsigned long long ull;

template<typename T>
std::ostream &operator<<(std::ostream &stream, const vector<T> &list) {
  for(const auto &item:list) {
    stream << item << " ";
  }
  return stream;
}
int main() {
  BigInt negative1(-1567);
  auto num = 18446744073709551615ULL;
  cout << num << endl;

  return 0;
}