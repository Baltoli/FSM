#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <map>
#include <optional>
#include <set>
#include <string>

class State {
  std::string name_;
  bool accepting_;
  bool initial_;
};

template<class T>
class Edge {
  std::shared_ptr<State> end_;
  std::optional<T> edge_value_;
};

template<class T>
class FiniteStateMachine {
  std::map<State, std::set<Edge<T>>> adjacency_; 
};

#include "finite_state_machine_impl.cc"

#endif
