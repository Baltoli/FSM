#include <iostream>

#include "finite_state_machine.h"

int main() {
  auto x = State{"jiwefo"};
  x.initial = true;

  auto y = State{"hello"};
  y.accepting = true;

  auto f = FiniteStateMachine<int>{};
  
  auto as = f.AddState(x);
  auto ay = f.AddState(y);
  f.AddEdge(as, as, 3);
  f.AddEdge(as, ay, 4);

  std::cout << f.Dot() << '\n';
  std::cout << f.IsDeterministic() << '\n';

  return 0;
}
