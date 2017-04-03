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
  auto e1 = f.AddEdge(as, as, 3);
  auto e2 = f.AddEdge(as, ay, 4);

  std::cout << f.Dot() << '\n';
  std::cout << f.IsDeterministic() << '\n';
  std::cout << e1.Accepts(3) << " " << e1.Accepts(2) << '\n';
  std::cout << e2.Accepts(3) << " " << e2.Accepts(4) << '\n';
  std::cout << e1.Accepts<int>(5, [=](auto e, auto t) { return e < t; }) << '\n';

  return 0;
}
