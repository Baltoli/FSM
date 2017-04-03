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
  f.AddEdge(as, ay);

  std::cout << f.Dot() << '\n';

  return 0;
}
