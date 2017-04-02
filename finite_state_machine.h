#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <map>
#include <optional>
#include <set>
#include <string>

struct State {
  State() {}

  State(std::string s) :
    name(s) {}

  std::string name = "";
  bool accepting = false;
  bool initial = false;
};

template<class T>
class Edge {
public:
  bool operator<(const Edge& other) const {
    return (end_ < other.end_) || 
           (end_ == other.end_ && edge_value_ < other.edge_value_);
  }
private:
  std::shared_ptr<State> end_;
  std::optional<T> edge_value_;
};

template<class T>
class FiniteStateMachine {
public:
  std::shared_ptr<State> AddState(State s);

  std::string Dot() const;
private:
  std::map<std::shared_ptr<State>, std::set<Edge<T>>> adjacency_; 
  std::set<std::shared_ptr<State>> states_;
};

#include "finite_state_machine_impl.cc"

#endif
