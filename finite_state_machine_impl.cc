#include <sstream>

template<class T>
std::shared_ptr<State> FiniteStateMachine<T>::AddState(State s)
{
  auto pointer = std::shared_ptr<State>{new State{s}};
  states_.insert(pointer);  
  adjacency_[pointer] = {};
  return pointer;
}

template<class T>
Edge<T> FiniteStateMachine<T>::AddEdge(std::shared_ptr<State> begin, 
                                       std::shared_ptr<State> end)
{
  auto edge = Edge<T>{end};
  adjacency_[begin].insert(edge);
  return edge;
}

template<class T>
Edge<T> FiniteStateMachine<T>::AddEdge(std::shared_ptr<State> begin, 
                                       std::shared_ptr<State> end, T val)
{
  auto edge = Edge<T>{end, val};
  adjacency_[begin].insert(edge);
  return edge;
}

template<class T>
bool FiniteStateMachine<T>::IsDeterministic() const {
  return std::all_of(adjacency_.begin(), adjacency_.end(),
    [=](auto adj_list) {
      auto epsilon_free = std::all_of(adj_list.second.begin(), adj_list.second.end(),
        [=](auto edge) {
          return !edge.IsEpsilon();
        }
      );

      auto edges = std::set<T>{};
      auto unique = true;
      for(const auto& edge : adj_list.second) {
        if(!edge.Value()) {
          continue;
        }

        auto found = edges.find(*edge.Value());
        if(found == edges.end()) {
          edges.insert(*edge.Value());
        } else {
          unique = false;
          break;
        }
      }

      return epsilon_free && unique;
    }
  );
}

/** Printing as Dot **/

template<class T>
std::string FiniteStateMachine<T>::Dot() const
{
  std::stringstream out;

  out << "digraph {\n";
  out << "  node[shape=circle]\n";
  out << "  graph[rankdir=LR]\n";
  for(const auto& adj_list : adjacency_) {
    out << "  " << adj_list.first->Dot() << '\n';
    for(const auto& edge : adj_list.second) {
      out << "  " << adj_list.first->name << " -> " << edge.Dot() << '\n';
    }
  }
  out << "}";

  return out.str();
}

std::string State::Dot() const
{
  std::stringstream out;

  out << name;

  if(accepting) {
    out << "[shape=doublecircle]";
  }

  if(initial) {
    out << ";secret [style=invis,shape=point];secret->" << name;
  }

  return out.str();
}

template<class T>
std::string Edge<T>::Dot() const {
  std::stringstream out;

  out << end_->name;
  out << "[label=\"  ";
  if(edge_value_) {
    out << *edge_value_;
  } else {
    out << "ε";
  }
  out << "\"]";

  return out.str();
}
