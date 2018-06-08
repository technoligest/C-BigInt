//
// Created by Yaser Alkayale on 2018-06-07.
//

#ifndef BIGINT2_TEST_H
#define BIGINT2_TEST_H

#include <vector>
#include <iostream>

class Test{
public:
  inline Test() {}

  inline explicit Test(const Test &baseInteger) : fullInteger_(baseInteger.fullInteger_) {};
//private:
  std::vector<int> fullInteger_;
};

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  out << "[";
  for(int i = 0; i + 1 < v.size(); ++i) {
    out << v[i] << ", ";
  }

  if(!v.empty()) out << v[v.size() - 1];
  out << "]";
  return out;
}


#endif //BIGINT2_TEST_H
