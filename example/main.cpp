#include "auto_dynamic_cast.hpp"
#include <iostream>

struct base {
  virtual ~base() {}
};

struct test1 : public base {
  void hello1() {
    std::cout << "It is test1 structure" << std::endl;
  }
};

struct test2 : public base {
  void hello2() {
    std::cout << "It is test2 structure" << std::endl;
  }
};

struct test3 : public base {
  void hello3() {
    std::cout << "It is test3 structure" << std::endl;
  }
};

int main() {
  base *example = new test1;

  // Nice C++17 syntax
  auto [it1, it2, it3] = auto_dynamic_cast<test1*, test2*, test3*>(example);

  // In C++11 and C++14 syntax is not so handsome
//   test1 *it1;
//   test2 *it2;
//   test3 *it3;
//
//   std::tie(it1, it2, it3) = auto_dynamic_cast<test1*, test2*, test3*>(example);

  if (it1) {
    it1->hello1(); // print It is test1 structure
  }
  if (it2) {
    it2->hello2(); // never call
  }

  if (it3) {
    it3->hello3(); // never call
  }

  delete example;
}
