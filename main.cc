#include "finite_state_machine.h"

int main() {
  auto x = State{"jiwefo"};
  auto f = FiniteStateMachine<int>{};
  
  f.AddState(x);

  return 0;
}
