#include <iostream>
#include <sstream>

template<class T>
std::shared_ptr<State> FiniteStateMachine<T>::AddState(State s) {
  auto pointer = std::shared_ptr<State>{new State{s}};
  states_.insert(pointer);  
  adjacency_[pointer] = {};
  return pointer;
}

template<class T>
std::string FiniteStateMachine<T>::Dot() const {
  std::stringstream out;

  out << "strict digraph {\n";
  for(const auto& adj_list : adjacency_) {
    out << *adj_list.first;
  }

  return out.str();
}

std::ostream& operator<<(std::ostream& stream, const State& state) {
  stream << state.name;
  return stream;
}
