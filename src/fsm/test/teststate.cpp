#include <fsm/state.h>

#include "catch.h"

#include <regex>

TEST_CASE("basic state operations") {
  SECTION("can default construct states") {
    State s;

    REQUIRE(s.name == "");
    REQUIRE(s.accepting == false);
    REQUIRE(s.initial == false);
  }

  SECTION("can construct states with a name") {
    State s("name");

    REQUIRE(s.name == "name");
    REQUIRE(s.accepting == false);
    REQUIRE(s.initial == false);
  }

  SECTION("can mutate states") {
    State s;

    s.name = "name";
    s.accepting = true;
    s.initial = true;

    REQUIRE(s.name == "name");
    REQUIRE(s.accepting == true);
    REQUIRE(s.initial == true);
  }
}

TEST_CASE("state DOT output") {
  SECTION("output includes name") {
    State s("name");
    std::regex r("name");

    REQUIRE(std::regex_search(s.Dot(), r));
  }

  SECTION("accepting output changes shape") {
    State s;
    s.accepting = true;
    std::regex r( R"(shape=.*)" );

    REQUIRE(std::regex_search(s.Dot(), r));
  }

  SECTION("initial output adds invisible") {
    State s;
    s.initial = true;
    std::regex i("invis");
    std::regex p("point");

    REQUIRE(std::regex_search(s.Dot(), i));
    REQUIRE(std::regex_search(s.Dot(), p));
  }
}

TEST_CASE("combined states") {
  SECTION("combining empty set") {
    std::set<std::shared_ptr<State>> e;
    auto c = State::Combined(e);

    REQUIRE(c.accepting == false);
    REQUIRE(c.initial == false);
  }

  SECTION("combining ordinary states") {
    auto s1 = std::make_shared<State>("s1");
    auto s2 = std::make_shared<State>("s2");
    auto s3 = std::make_shared<State>("s3");
    auto set = std::set<decltype(s1)>{ s1, s2, s3 };

    auto c = State::Combined(set);
  
    REQUIRE(std::all_of(set.begin(), set.end(), [&](auto state) {
      std::regex r(state->name);
      return std::regex_search(c.name, r);
    }));
    REQUIRE(c.accepting == false);
    REQUIRE(c.initial == false);
  }

  SECTION("one accepting") {
    auto s1 = std::make_shared<State>("s1");
    s1->accepting = true;
    auto s2 = std::make_shared<State>("s2");
    auto s3 = std::make_shared<State>("s3");
    auto set = std::set<decltype(s1)>{ s1, s2, s3 };

    auto c = State::Combined(set);
  
    REQUIRE(std::all_of(set.begin(), set.end(), [&](auto state) {
      std::regex r(state->name);
      return std::regex_search(c.name, r);
    }));
    REQUIRE(c.accepting == true);
    REQUIRE(c.initial == false);
  }

  SECTION("one initial") {
    auto s1 = std::make_shared<State>("s1");
    s1->initial = true;
    auto s2 = std::make_shared<State>("s2");
    auto s3 = std::make_shared<State>("s3");
    auto set = std::set<decltype(s1)>{ s1, s2, s3 };

    auto c = State::Combined(set);
  
    REQUIRE(std::all_of(set.begin(), set.end(), [&](auto state) {
      std::regex r(state->name);
      return std::regex_search(c.name, r);
    }));
    REQUIRE(c.accepting == false);
    REQUIRE(c.initial == false);
  }

  SECTION("only initial") {
    auto s1 = std::make_shared<State>("s1");
    s1->initial = true;
    auto set = std::set<decltype(s1)>{ s1 };

    auto c = State::Combined(set);
  
    REQUIRE(std::all_of(set.begin(), set.end(), [&](auto state) {
      std::regex r(state->name);
      return std::regex_search(c.name, r);
    }));
    REQUIRE(c.accepting == false);
    REQUIRE(c.initial == true);
  }
}
