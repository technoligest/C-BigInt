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
  cout << std::numeric_limits<ull>::max() << endl;
  return 0;
}