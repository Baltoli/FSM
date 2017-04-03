#include <iostream>

#include "finite_state_machine.h"

int main() {
  auto q1 = State{"1"};
  q1.initial = true;

  auto q2 = State{"2"};

  auto q3 = State{"3"};
  q3.accepting = true;

  auto q4 = State{"4"};
  q4.accepting = true;

  auto f = FiniteStateMachine<int>{};
  auto q1a = f.AddState(q1);
  auto q2a = f.AddState(q2);
  auto q3a = f.AddState(q3);
  auto q4a = f.AddState(q4);

  f.AddEdge(q1a, q2a, 0);
  f.AddEdge(q1a, q3a);

  f.AddEdge(q2a, q2a, 1);
  f.AddEdge(q2a, q4a, 1);

  f.AddEdge(q3a, q2a);
  f.AddEdge(q3a, q4a, 0);

  f.AddEdge(q4a, q3a, 0);
  
  std::cout << f.Dot() << '\n';
  std::cout << f.Deterministic().Dot() << '\n';

  return 0;
}
