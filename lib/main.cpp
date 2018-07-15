#include <iostream>
#include <vector>
#include <bitset>
#include "Exception.h"

#define _DEBUG

#include "BigInt.h"

using std::cout;
using std::endl;
using bigint::BigInt;
typedef unsigned long long ull;
#define SCPP_THROW_EXCEPTION_ON_BUG

//template<typename T>
//std::ostream &operator<<(std::ostream &stream, const vector<T> &list) {
//  for(const auto &item:list) {
//    stream << item << " ";
//  }
//  return stream;
//}
void method(){
  throw bigint::Exception(bigint::Exception::ErrorTypes::INTERNAL_ERROR,__LINE__,__FILE__,"There is something wrong.");
}
int main(){
  //cout << "\033[1;31mbold red text\033[0m\n";
  try{
    method();
  }
  catch(bigint::Exception e){
    cout<<e.what()<<endl;
  }
  return 0;
}