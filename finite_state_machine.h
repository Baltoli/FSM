#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <map>
#include <set>
#include <string>

#include "edge.h"
#include "state.h"

template<class T>
class FiniteStateMachine {
public:
  std::shared_ptr<State> AddState(State s);
  Edge<T> AddEdge(std::shared_ptr<State> begin, std::shared_ptr<State> end);
  Edge<T> AddEdge(std::shared_ptr<State> begin, std::shared_ptr<State> end, T val);

  bool IsDeterministic() const;

  std::set<std::shared_ptr<State>> EpsilonClosure(std::shared_ptr<State> state);

  FiniteStateMachine<T> EpsilonFree();

  std::string Dot() const;
private:
  std::map<std::shared_ptr<State>, std::set<Edge<T>>> adjacency_; 
  std::set<std::shared_ptr<State>> states_;
};

#include "finite_state_machine_impl.cc"

#endif
