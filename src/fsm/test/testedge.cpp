#include <fsm/edge.h>

#include "catch.h"

#include <regex>

TEST_CASE("constructing edges") {
  SECTION("can construct epsilon edges") {
    auto s = std::make_shared<State>("s");
    Edge<int> e(s);

    REQUIRE(e.IsEpsilon());
    REQUIRE(e.End() == s);
  }

  SECTION("can construct labelled edges") {
    auto s = std::make_shared<State>("s");
    Edge<int> e(s, 1);

    REQUIRE(!e.IsEpsilon());
    REQUIRE(e.End() == s);
    REQUIRE(e.Value() == 1);
  }
}

TEST_CASE("edge DOT output") {
  auto s = std::make_shared<State>("name");
  Edge<int> e(s);
  std::regex r("name");
  std::regex l("label=.*");

  REQUIRE(std::regex_search(e.Dot(), r));
  REQUIRE(std::regex_search(e.Dot(), l));
}

TEST_CASE("edge acceptance") {
  auto s = std::make_shared<State>("s");
  auto ee = Edge<int>(s);
  auto le = Edge<int>(s, 3);

  SECTION("epsilon doesn't accept") {
    REQUIRE(!ee.Accepts<int>(3, std::equal_to<int>{}));
  }

  SECTION("labelled does accept") {
    REQUIRE(le.Accepts<int>(3, std::equal_to<int>{}));
  }

  SECTION("custom acceptance functions") {
    const auto f = [](auto e, auto v) {
      return abs(e - v) <= 3;
    };

    REQUIRE(le.Accepts<int>(0, f));
    REQUIRE(!le.Accepts<int>(7, f));
  }
}

TEST_CASE("edge transducing") {
  auto s = std::make_shared<State>("s");
  auto e = Edge<int>(s, 1);

  SECTION("can transduce a value") {
    const auto f1 = [](auto e, auto v) {
      return e == v;
    };

    const auto f2 = [](auto e, auto v) {
      return e + v;
    };

    REQUIRE((!e.Transduce<int, bool>(0, f1)));
    REQUIRE((e.Transduce<int, bool>(1, f1)));
    REQUIRE((e.Transduce<int, int>(7, f2) == 8));
  }
}
