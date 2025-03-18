#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"

#include "QuickSelect.h"
#include <vector>
#include <algorithm>
#include <random>

TEST_CASE("Quick select iterative"){
  auto rng = std::default_random_engine {};
  std::vector<int> list = {0,1,2,3,4,5,6,7,8,9,10};

  REQUIRE(Quickselect(list, 4) == 3);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 3) == 2);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 8) == 7);

}


TEST_CASE("Quick select recursive"){
  auto rng = std::default_random_engine {};
  std::vector<int> list = {0,1,2,3,4,5,6,7,8,9,10};

  REQUIRE(Quickselect_rec(list, 4) == 3);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 3) == 2);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 8) == 7);

}

TEST_CASE("Quick select iterative random"){
  auto rng = std::default_random_engine {};
  std::vector<int> list(1000);
  std::generate(list.begin(), list.end(), rng);
  std::sort(list.begin(), list.end());
  int a = list[4], b = list[3], c = list[8], d = list[101];

  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 5) == a);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 4) == b);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 9) == c);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect(list, 102) == d);
}


TEST_CASE("Quick select recursive random"){
  auto rng = std::default_random_engine {};
  std::vector<int> list(1000);
  std::generate(list.begin(), list.end(), rng);
  std::sort(list.begin(), list.end());
  int a = list[4], b = list[3], c = list[8], d = list[101];

  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 5) == a);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 4) == b);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 9) == c);
  std::shuffle(list.begin(), list.end(), rng);
  REQUIRE(Quickselect_rec(list, 102) == d);
}