#include <fsm/fsm.h>

#include "catch.h"

#include <iostream>
#include <random>

TEST_CASE("constructing cross products") {
  FiniteStateMachine<int> a;
  auto as = a.AddStates(10);
  as[0]->initial = true;
  as[9]->accepting = true;
  for(auto i = 0; i < 9; i++) {
    a.AddEdge(as[i], as[i+1], i);
  }

  FiniteStateMachine<int> b;
  auto bs = b.AddStates(10);
  bs[0]->initial = true;
  bs[9]->accepting = true;
  for(auto i = 0; i < 9; i++) {
    b.AddEdge(bs[i], bs[i+1], (i*10)+1);
  }

  auto c = a.CrossProduct(b);

  auto a_seq = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
  REQUIRE(a.AcceptsSequence(std::begin(a_seq), std::end(a_seq)));
  REQUIRE(!b.AcceptsSequence(std::begin(a_seq), std::end(a_seq)));
  REQUIRE(c.AcceptsSequence(std::begin(a_seq), std::end(a_seq)));

  auto b_seq = { 1, 11, 21, 31, 41, 51, 61, 71, 81 };
  REQUIRE(!a.AcceptsSequence(std::begin(b_seq), std::end(b_seq)));
  REQUIRE(b.AcceptsSequence(std::begin(b_seq), std::end(b_seq)));
  REQUIRE(c.AcceptsSequence(std::begin(b_seq), std::end(b_seq)));

  auto no_seq = { 0, 1, 2, 1, 11, 3, 4, 5, 21 };
  REQUIRE(!a.AcceptsSequence(std::begin(no_seq), std::end(no_seq)));
  REQUIRE(!b.AcceptsSequence(std::begin(no_seq), std::end(no_seq)));
  REQUIRE(!c.AcceptsSequence(std::begin(no_seq), std::end(no_seq)));

  auto mix_seq = { 0, 1, 2, 3, 1, 11, 21, 31, 4, 41, 51, 5, 6, 61, 7, 8 };
  REQUIRE(!a.AcceptsSequence(std::begin(mix_seq), std::end(mix_seq)));
  REQUIRE(!b.AcceptsSequence(std::begin(mix_seq), std::end(mix_seq)));
  REQUIRE(c.AcceptsSequence(std::begin(mix_seq), std::end(mix_seq)));
}

TEST_CASE("reversing FSMs") {
  FiniteStateMachine<int> a;
  auto as = a.AddStates(4);
  as[0]->initial = true;
  as[3]->accepting = true;

  a.AddEdge(as[0], as[1], 0);
  a.AddEdge(as[0], as[2], 1);
  a.AddEdge(as[2], as[3], 2);
  a.AddEdge(as[1], as[3], 2);

  std::cout << a.Relabeled().Dot() << '\n';
  std::cout << a.Deterministic().Relabeled().Dot() << '\n';
  std::cout << a.Minimised().Relabeled().Dot() << '\n';
}
