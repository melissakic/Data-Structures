#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "list.hpp"

#include <initializer_list>

TEST_CASE("Expects to construct empty array") {
  mojaLista<int> mojaLista;
  CHECK_EQ(mojaLista.size(), 0);
}

TEST_CASE("Expects to initialize mojaLista<int> using initializer_list") {
  mojaLista<int> mojaLista{1, 2, 3, 4, 5, 0, -1, -2, -3, -4, -5};
  CHECK_EQ(mojaLista.size(), 11);
  auto it = mojaLista.begin();
  for (auto i = 1; i <= 5; ++i)
    CHECK_EQ(*(it++), i);
}

TEST_CASE("Expects to have a proper copy constructor") {
  mojaLista<int> mojaLista1{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  mojaLista<int> mojaLista2 = mojaLista1;
  CHECK_EQ(mojaLista1.size(), 10);
  CHECK_EQ(mojaLista2.size(), 10);
  auto it1 = mojaLista1.begin();
  auto it2 = mojaLista2.begin();
  for (auto i = 9; i >= 0; --i) {
    CHECK_EQ(*(it1++), i + 1);
    CHECK_EQ(*(it2++), i + 1);
  }
  it1 = mojaLista1.begin();
  it2 = mojaLista2.begin();
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&(*it1), &(*it2));
}

TEST_CASE("Expects to have a proper move constructor") {
  mojaLista<int> mojaLista1{1, 3, 5, 7, 9};
  mojaLista<int> mojaLista2 = std::move(mojaLista1);
  CHECK_EQ(mojaLista2.size(), 5);
  auto it = mojaLista2.begin();
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(*(it++), 2 * i + 1);
  }
  CHECK_EQ(mojaLista1.size(), 0);
}


TEST_CASE("Expects to have a proper copy operator=") {
  mojaLista<int> mojaLista1{0, 2, 4, 6, 8};
  mojaLista<int> mojaLista2{1, 3, 5, 7, 9, 12, 15};
  mojaLista2 = mojaLista1;
  // Did you replace the size?
  CHECK_EQ(mojaLista2.size(), 5);
  auto it1=mojaLista1.begin();
  auto it2=mojaLista2.begin();
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(*(it1++), 2 * i);
    CHECK_EQ(*(it2++), 2 * i);
  }
  it1=mojaLista1.begin();
  it2=mojaLista2.begin();
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&(*it1), &(*it2));
}

TEST_CASE("Expects to be able to append copy operator=") {
  mojaLista<int> mojaLista1{0, 2, 4, 6, 8};
  mojaLista<int> mojaLista2{1, 3, 5, 7, 9};
  mojaLista<int> mojaLista3{-5, -4, -3, -2, -1, 0};
  mojaLista1 = mojaLista2 = mojaLista3;
  CHECK_EQ(mojaLista1.size(), 6);
  CHECK_EQ(mojaLista2.size(), 6);
  auto it1=mojaLista1.begin();
  auto it2=mojaLista2.begin();
  auto it3=mojaLista3.begin();

  for (auto i = 0; i < 6; ++i) {
    CHECK_EQ(*(it1++), i - 5);
    CHECK_EQ(*(it2++), i - 5);
    CHECK_EQ(*(it3++), i - 5);
  }
}

TEST_CASE("Expects to have a proper move operator=") {
  mojaLista<int> mojaLista1{0, 2, 4, 6};
  mojaLista<int> mojaLista2{1, 3, 5, 7, 9};
  mojaLista2 = std::move(mojaLista1);
  CHECK_EQ(mojaLista1.size(), 0);
  auto it = mojaLista2.begin();
  for (auto i = 0; i < 4; ++i) {
    CHECK_EQ(*it, 2 * i);
    it++;
  }
  CHECK_EQ(mojaLista2.size(), 4);
}

TEST_CASE("Expects to be able to append move operator=") {
  mojaLista<int> mojaLista1{0, 2, 4, 6, 8};
  mojaLista<int> mojaLista2{1, 3, 5, 7, 9};
  mojaLista<int> mojaLista3{-5, -4, -3, -2, -1, 0};
  mojaLista1 = mojaLista2 = std::move(mojaLista3);
  CHECK_EQ(mojaLista1.size(), 6);
  CHECK_EQ(mojaLista2.size(), 6);
  CHECK_EQ(mojaLista3.size(), 0);
  int i = -5;
  for(auto it = mojaLista1.begin();it!=mojaLista1.end();++it)
  {
    CHECK_EQ(*it,i++);
  }
  i = -5;
  for(auto it = mojaLista2.begin();it!=mojaLista2.end();++it)
  {
    CHECK_EQ(*it,i++);
  }
}

TEST_CASE("Expects pop_back(), front() and back() to be implemented") {
  mojaLista<int> mojaLista1{1, 2, 3};
  CHECK_EQ(mojaLista1.back(), 3);
  CHECK_EQ(mojaLista1.front(), 1);
  mojaLista1.pop_back();
  CHECK_EQ(mojaLista1.back(), 2);
  CHECK_EQ(mojaLista1.front(), 1);
  mojaLista1.pop_back();
  CHECK_EQ(mojaLista1.back(), 1);
  CHECK_EQ(mojaLista1.front(), 1);
}


TEST_CASE("Expects operator== and operator!= to be implemented") {
  mojaLista<int> mojaLista1{4, 5, 1, 2, 3, 7, 6};
  mojaLista<int> mojaLista2{4, 5, 1, 2, 3, 7, 6};
  CHECK_EQ(mojaLista1, mojaLista2);
  mojaLista1.pop_back();
  CHECK_NE(mojaLista1, mojaLista2);
}

TEST_CASE("Expects find to be implemented") {
  mojaLista<int> mojaLista1{4, 5, 1, 2, 3, 7, 6};
  auto it = mojaLista1.find(1);
  CHECK_EQ(*it,1);
  it = mojaLista1.find(10);
  CHECK_EQ(it,mojaLista1.end());
}


TEST_CASE("Expects insert and erase to be implemented") {
  mojaLista<int> mojaLista1{1,3,5};
  auto it = mojaLista1.begin();
  mojaLista1.erase(it);
  it = mojaLista1.begin();
  mojaLista1.insert(it,2);
  it = mojaLista1.begin();
  mojaLista1.insert(it,1);
  it = mojaLista1.begin();
  it++;
  it++;
  it++;
  mojaLista1.insert(it,4);
  auto it1=mojaLista1.begin();
  for (auto i = 1; i < 6; ++i) {
    CHECK_EQ(*(it1++), i);
  }
}

TEST_CASE("Expects push_front, push_back, pop_front, pop_back to be implemented") {
  mojaLista<int> mojaLista1{1};
  mojaLista1.push_front(0);
  mojaLista1.push_back(2);
  mojaLista1.pop_front();
  mojaLista1.pop_back();
  CHECK_EQ(mojaLista1.size(),1);
  CHECK_EQ(*(mojaLista1.begin()),1);
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 10000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 10000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}


TEST_CASE("Expects to be able to accommodate 100000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 100000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 1000000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 1000000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 10000000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 100000000 number") {
  mojaLista<int> mojaLista1;
  unsigned long long i = 0;
  while (i < 100000000) {
    mojaLista1.push_back(++i);
    CHECK_EQ(mojaLista1.size(), i);
  }
}
