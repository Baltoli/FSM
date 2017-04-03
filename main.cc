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
  auto az = f.AddState(State{"quh"});

  auto e1 = f.AddEdge(as, as, 3);
  auto e3 = f.AddEdge(as, ay);
  auto e2 = f.AddEdge(as, ay, 4);
  f.AddEdge(ay, az);

  std::cout << f.Dot() << '\n';

  std::cout << "Epsilon for " << as->name << '\n';
  for(const auto& eps : f.EpsilonClosure(as)) {
    std::cout << "  " << eps->name << '\n';
  }

  return 0;
}
