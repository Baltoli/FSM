#include <cassert>
#include <queue>
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
std::shared_ptr<State> FiniteStateMachine<T>::InitialState() const
{
  auto found = std::find_if(adjacency_.begin(), adjacency_.end(),
    [=](auto p) { 
      return p.first->initial; 
    }
  );

  assert(found != adjacency_.end());
  return found->first;
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

template<class T>
std::set<std::shared_ptr<State>>
  FiniteStateMachine<T>::EpsilonClosure(std::shared_ptr<State> state)
{
  auto ret = std::set<std::shared_ptr<State>>{ state };
  auto visited = decltype(ret){};

  auto work_queue = std::queue<std::shared_ptr<State>>{};
  work_queue.push(state);

  while(!work_queue.empty()) {
    auto next = work_queue.front();
    work_queue.pop();

    if(visited.find(next) != visited.end()) {
      continue;
    } else {
      visited.insert(next);
    }

    for(const auto& edge : adjacency_[next]) {
      if(edge.IsEpsilon()) {
        ret.insert(edge.End());
        work_queue.push(edge.End());
      }
    }
  }

  return ret;
}

template<class T>
FiniteStateMachine<T> FiniteStateMachine<T>::EpsilonFree()
{
  auto closure_map = std::map<std::shared_ptr<State>, std::shared_ptr<State>>{};
  auto eps_free = FiniteStateMachine<T>{};

  for(const auto& adj_list : adjacency_) {
    const auto& state = adj_list.first;
    auto combined = State::Combined(EpsilonClosure(state));
    combined.initial = state->initial;

    auto added = eps_free.AddState(combined);
    closure_map[state] = added;
  }

  for(const auto& adj_list : adjacency_) {
    const auto& state = adj_list.first;

    for(const auto& member : EpsilonClosure(state)) {
      for(const auto& edge : adjacency_[member]) {
        if(!edge.IsEpsilon()) {
          eps_free.AddEdge(closure_map[state], closure_map[edge.End()], *edge.Value());
        }
      }
    }
  }

  return eps_free;
}

template<class T>
FiniteStateMachine<T> FiniteStateMachine<T>::Deterministic()
{
  auto eps_free = EpsilonFree();
  auto dfa = FiniteStateMachine<T>{};

  auto initial_state = eps_free.InitialState();
  auto work_queue = std::queue<std::set<std::shared_ptr<State>>>{};
  work_queue.push({initial_state});

  auto combined = std::map<std::set<std::shared_ptr<State>>, std::shared_ptr<State>>{};
  auto visited = std::set<std::set<std::shared_ptr<State>>>{};

  while(!work_queue.empty()) {
    auto next = work_queue.front();
    work_queue.pop();

    if(visited.find(next) == visited.end()) {
      visited.insert(next);
    } else {
      continue;
    }

    if(combined.find(next) == combined.end()) {
      auto cs = State::Combined(next);
      auto csa = dfa.AddState(cs);
      combined[next] = csa;
    }

    auto reachable = std::map<T, std::set<std::shared_ptr<State>>>{};
    for(const auto& state : next) {
      for(const auto& edge : eps_free.adjacency_[state]) {
        reachable[*edge.Value()].insert(edge.End());
      }
    }

    for(const auto& reach_pair : reachable) {
      work_queue.push(reach_pair.second);

      if(combined.find(reach_pair.second) == combined.end()) {
        auto cs = State::Combined(reach_pair.second);
        auto csa = dfa.AddState(cs);
        combined[reach_pair.second] = csa;
      }

      dfa.AddEdge(combined[next], combined[reach_pair.second], reach_pair.first);
    }
  }

  return dfa;
}

template<class T>
template<class Iterator>
bool FiniteStateMachine<T>::AcceptsSequence(Iterator begin, Iterator end)
{
  static_assert(std::is_same<typename std::iterator_traits<Iterator>::value_type, T>::value);

  auto state = InitialState();
  for(auto it = begin; it != end; it++) {
    auto accepting_edge = std::find_if(adjacency_[state].begin(), adjacency_[state].end(),
      [=](Edge<T> edge) {
        return edge.Accepts(*it);
      }
    );

    if(accepting_edge == adjacency_[state].end()) {
      return false;
    } else {
      state = accepting_edge->End();
    }
  }

  return true;
}

template<class T>
template<class Iterator, class E>
bool FiniteStateMachine<T>::AcceptsSequence(Iterator begin, Iterator end, 
                                            std::function<bool (E,T)> acc)
{
  static_assert(std::is_same<typename std::iterator_traits<Iterator>::value_type, E>::value);

  auto state = InitialState();
  for(auto it = begin; it != end; it++) {
    auto accepting_edge = std::find_if(adjacency_[state].begin(), adjacency_[state].end(),
      [=](Edge<T> edge) {
        return edge.Accepts(*it, acc);
      }
    );

    if(accepting_edge == adjacency_[state].end()) {
      return false;
    } else {
      state = accepting_edge->End();
    }
  }

  return true;
}

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
      out << "  \"" << adj_list.first->name << "\" -> " << edge.Dot() << "\n";
    }
  }
  out << "}";

  return out.str();
}
