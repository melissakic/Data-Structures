#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MojVektor.hpp"

#include <initializer_list>

TEST_CASE("Expects to construct empty array") {
  MojVector<int> mojNiz;
  CHECK_EQ(mojNiz.size(), 0);
}

TEST_CASE("Expects method at to throw when element at 0 index does not exist") {
  MojVector<int> mojNiz;
  CHECK_THROWS_AS(mojNiz.at(0), std::out_of_range);
}

TEST_CASE(
    "Expects method at to throw when element at -1 index does not exist") {
  MojVector<int> mojNiz;
  CHECK_THROWS_AS(mojNiz.at(-1), std::out_of_range);
}

TEST_CASE("Expects to initialize MojVector<int> using initializer_list") {
  MojVector<int> mojNiz{1, 2, 3, 4, 5, 0, -1, -2, -3, -4, -5};
  CHECK_EQ(mojNiz.size(), 11);
  for (auto i = 1; i <= 5; ++i)
    CHECK_EQ(mojNiz.at(i - 1), i);
  for (auto i = 0; i >= -5; --i)
    CHECK_EQ(mojNiz.at(std::abs(i) + 5), i);
}

TEST_CASE("Expects to have const access to at and size method") {
  MojVector<int> mojNiz{1, 2, 3, 4, 5};
  const auto &mojConstNiz = mojNiz;
  CHECK_EQ(mojConstNiz.size(), 5);
  for (auto i = 0; i < 5; ++i)
    CHECK_EQ(mojConstNiz.at(i), i + 1);
}

TEST_CASE("Expects at method to be able to modify the object within "
          "MojVector<int>") {
  MojVector<int> mojNiz{1, 2, 3, 4, 5, 6};
  mojNiz.at(3) = 19;
  CHECK_EQ(mojNiz.size(), 6);
  CHECK_EQ(mojNiz.at(3), 19);
  for (auto i = 0; i < 3; ++i)
    CHECK_EQ(mojNiz.at(i), i + 1);
  for (auto i = 4; i < 6; ++i)
    CHECK_EQ(mojNiz.at(i), i + 1);
}

TEST_CASE("Expects to have a proper copy constructor") {
  MojVector<int> mojNiz{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  MojVector<int> mojNiz2 = mojNiz;
  CHECK_EQ(mojNiz.size(), 10);
  CHECK_EQ(mojNiz2.size(), 10);
  for (auto i = 9; i >= 0; --i) {
    CHECK_EQ(mojNiz.at(9 - i), i + 1);
    CHECK_EQ(mojNiz2.at(9 - i), i + 1);
  }
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&mojNiz.at(0), &mojNiz2.at(0));
}

TEST_CASE("Expects to have a proper move constructor") {
  MojVector<int> mojNiz1{1, 3, 5, 7, 9};
  MojVector<int> mojNiz2 = std::move(mojNiz1);
  CHECK_EQ(mojNiz2.size(), 5);
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(mojNiz2.at(i), 2 * i + 1);
  }
  CHECK_EQ(mojNiz1.size(), 0);
}

TEST_CASE("Expects not to reset dynamic array on destructor when moved") {
  MojVector<int> *mojNiz;
  {
    MojVector<int> mojNizScoped{1, 3, 5, 7, 9};
    mojNiz = new MojVector<int>(std::move(mojNizScoped));
    CHECK_EQ(mojNizScoped.size(), 0);
  }
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(mojNiz->at(i), 2 * i + 1);
  }
}

TEST_CASE("Expects to have an operator[]") {
  MojVector<int> mojNiz{1, 3, 5, 7, 9};
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(mojNiz[i], 2 * i + 1);
  }
}

TEST_CASE("Expects to be able to modify an element using operator[]") {
  MojVector<int> mojNiz{1, 3, 5, 7, 9};
  mojNiz[4] = 12;
  for (auto i = 0; i < 4; ++i) {
    CHECK_EQ(mojNiz[i], 2 * i + 1);
  }
  CHECK_EQ(mojNiz[4], 12);
}

TEST_CASE("Expects to be able to use operator[] in const context") {
  MojVector<int> mojNiz{1, 3, 5, 7, 9};
  const MojVector<int> &mojNizConstRef = mojNiz;
  for (auto i = 0; i < 4; ++i) {
    CHECK_EQ(mojNizConstRef[i], 2 * i + 1);
  }
}

TEST_CASE("Expects to have a proper copy operator=") {
  MojVector<int> mojNiz1{0, 2, 4, 6, 8};
  MojVector<int> mojNiz2{1, 3, 5, 7, 9, 12, 15};
  mojNiz2 = mojNiz1;
  // Did you replace the size?
  CHECK_EQ(mojNiz2.size(), 5);
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(mojNiz1[i], 2 * i);
    CHECK_EQ(mojNiz2[i], 2 * i);
  }
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&mojNiz1[0], &mojNiz2[0]);
}

TEST_CASE("Expects to be able to append copy operator=") {
  MojVector<int> mojNiz1{0, 2, 4, 6, 8};
  MojVector<int> mojNiz2{1, 3, 5, 7, 9};
  MojVector<int> mojNiz3{-5, -4, -3, -2, -1, 0};
  mojNiz1 = mojNiz2 = mojNiz3;
  CHECK_EQ(mojNiz1.size(), 6);
  CHECK_EQ(mojNiz2.size(), 6);
  for (auto i = 0; i < 6; ++i) {
    CHECK_EQ(mojNiz1[i], i - 5);
    CHECK_EQ(mojNiz2[i], i - 5);
    CHECK_EQ(mojNiz3[i], i - 5);
  }
}

TEST_CASE("Expects to have a proper move operator=") {
  MojVector<int> mojNiz1{0, 2, 4, 6};
  MojVector<int> mojNiz2{1, 3, 5, 7, 9};
  mojNiz2 = std::move(mojNiz1);
  CHECK_EQ(mojNiz1.size(), 0);
  for (auto i = 0; i < 4; ++i) {
    CHECK_EQ(mojNiz2[i], 2 * i);
  }
  CHECK_EQ(mojNiz2.size(), 4);
}

TEST_CASE("Expects not to reset dynamic array on destructor when moved=") {
  MojVector<int> mojNiz1;
  {
    MojVector<int> mojNiz2{1, 3, 5, 7, 9};
    mojNiz1 = std::move(mojNiz2);
    CHECK_EQ(mojNiz2.size(), 0);
  }
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(mojNiz1[i], 2 * i + 1);
  }
}

TEST_CASE("Expects to be able to append move operator=") {
  MojVector<int> mojNiz1{0, 2, 4, 6, 8};
  MojVector<int> mojNiz2{1, 3, 5, 7, 9};
  MojVector<int> mojNiz3{-5, -4, -3, -2, -1, 0};
  mojNiz1 = mojNiz2 = std::move(mojNiz3);
  CHECK_EQ(mojNiz1.size(), 6);
  CHECK_EQ(mojNiz2.size(), 6);
  CHECK_EQ(mojNiz3.size(), 0);
  for (auto i = 0; i < 6; ++i) {
    CHECK_EQ(mojNiz1[i], i - 5);
    CHECK_EQ(mojNiz2[i], i - 5);
  }
}

TEST_CASE("Expects pop_back(), front() and back() to be implemented") {
  MojVector<int> mojNiz1{1, 2, 3};
  CHECK_EQ(mojNiz1.back(), 3);
  CHECK_EQ(mojNiz1.front(), 1);
  mojNiz1.pop_back();
  CHECK_EQ(mojNiz1.back(), 2);
  CHECK_EQ(mojNiz1.front(), 1);
  mojNiz1.pop_back();
  CHECK_EQ(mojNiz1.back(), 1);
  CHECK_EQ(mojNiz1.front(), 1);
}

TEST_CASE("Expects operator== and operator!= to be implemented") {
  MojVector<int> mojNiz1{4, 5, 1, 2, 3, 7, 6};
  MojVector<int> mojNiz2{4, 5, 1, 2, 3, 7, 6};
  CHECK_EQ(mojNiz1, mojNiz2);
  mojNiz1.pop_back();
  CHECK_NE(mojNiz1, mojNiz2);
}

TEST_CASE("Expects operator== and operator!= to be implemented") {
  MojVector<int> mojNiz{1, 2};
  mojNiz.resize(5);
  CHECK_EQ(mojNiz.size(), 5);
  CHECK_EQ(mojNiz, MojVector<int>{1, 2, 0, 0, 0});
}

TEST_CASE("Expects iterator to be implemented along with begin() and end()") {
  MojVector<int> mojNiz1{1, 2, 3};
  auto it1 = mojNiz1.begin();
  *it1 = 4;
  ++it1;
  CHECK_EQ(mojNiz1[0], 4);
  CHECK_EQ(*it1, 2);
  it1 = it1 + 1;
  CHECK_EQ(*it1, 3);
  it1 = it1 - 1;
  CHECK_EQ(*it1, 2);
  --it1;
  *it1 = 1;
  MojVector<int> mojNiz2{1, 2, 3};
  CHECK_EQ(mojNiz1, mojNiz2);
}

TEST_CASE("Expects insert and erase to be implemented") {
  MojVector<int> mojNiz1{1, 2, 3};
  mojNiz1.insert(mojNiz1.begin(), 4);
  CHECK_EQ(mojNiz1[0], 4);
  mojNiz1.insert(mojNiz1.begin() + 1, 5);
  CHECK_EQ(mojNiz1[0], 4);
  CHECK_EQ(mojNiz1[1], 5);
  mojNiz1.insert(mojNiz1.end(), 6);
  CHECK_EQ(mojNiz1[5], 6);
  mojNiz1.insert(mojNiz1.end() - 1, 7);
  CHECK_EQ(mojNiz1[5], 7);
  MojVector<int> mojNiz2{4, 5, 1, 2, 3, 7, 6};
  CHECK_EQ(mojNiz1, mojNiz2);
  mojNiz1.erase(mojNiz1.end() - 2);
  CHECK_EQ(mojNiz1[5], 6);
  mojNiz1.erase(mojNiz1.end() - 1);
  CHECK_EQ(mojNiz1[4], 3);
  mojNiz1.erase(mojNiz1.begin() + 1);
  mojNiz1.erase(mojNiz1.begin());
  MojVector<int> mojNiz3{1, 2, 3};
  CHECK_EQ(mojNiz1, mojNiz3);
}

TEST_CASE("Expects range based erase to be implemented") {
  MojVector<int> mojNiz1{1, 2, 3, 4, 5, 6, 7};
  MojVector<int> mojNiz2 = mojNiz1;
  MojVector<int> mojNiz3 = mojNiz2;

  mojNiz1.erase(mojNiz1.begin() + 1, mojNiz1.end() - 2);
  CHECK_EQ(mojNiz1, MojVector<int>{1, 6, 7});

  mojNiz2.erase(mojNiz2.begin(), mojNiz2.end() - 1);
  CHECK_EQ(mojNiz2, MojVector<int>{7});

  mojNiz3.erase(mojNiz3.begin() + 1, mojNiz3.end());
  CHECK_EQ(mojNiz3, MojVector<int>{1});
}

TEST_CASE("Expects find method to be implemented") {
  MojVector<int> mojNiz1{1, 2, 3, 4, 5, 6, 7};

  auto it = mojNiz1.find(5);

  CHECK(it < mojNiz1.end());
  CHECK(mojNiz1.begin() < it);
  CHECK_EQ(it, mojNiz1.begin() + 4);
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  MojVector<int> mojNiz1;
  int i= 0;
  while (i < 10000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  MojVector<int> mojNiz1;
  unsigned long long i = 0;
  while (i < 10000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}

// CHALLENGE
// If you can make these tests finish in less than a minute each, you've done a
// great job
TEST_CASE("Expects to be able to accommodate 100000 number") {
  MojVector<int> mojNiz1;
  unsigned long long i = 0;
  while (i < 100000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 1000000 number") {
  MojVector<int> mojNiz1;
  unsigned long long i = 0;
  while (i < 1000000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000000 number") {
  MojVector<int> mojNiz1;
  unsigned long long i = 0;
  while (i < 10000000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 100000000 number") {
  MojVector<int> mojNiz1;
  unsigned long long i = 0;
  while (i < 100000000) {
    mojNiz1.push_back(++i);
    CHECK_EQ(mojNiz1.size(), i);
  }
}
