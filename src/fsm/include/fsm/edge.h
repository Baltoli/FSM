#ifndef FSM_EDGE_H
#define FSM_EDGE_H

#include <fsm/state.h>

#include <functional>
#include <memory>
#include <string>

template<class T>
class Edge {
public:
  Edge(std::shared_ptr<State> end) :
    end_(end), edge_value_(nullptr) {}

  Edge(std::shared_ptr<State> end, T val) :
    end_(end), edge_value_(new T{val}) {}

  template<class E>
  bool Accepts(E val, std::function<bool (E,T)>) const;

  template<class E, class O>
  O Transduce(E val, std::function<O (E,T)> output) const;

  bool IsEpsilon() const { return !edge_value_; }

  const T& Value() const { return *edge_value_; }
  std::shared_ptr<State> End() const { return end_; }

  bool operator<(const Edge& other) const;

  std::string Dot() const;
private:
  std::shared_ptr<State> end_;
  std::shared_ptr<T> edge_value_;
};

template<class T>
template<class E>
bool Edge<T>::Accepts(E val, std::function<bool (E,T)> acceptor) const
{
  return edge_value_ && acceptor(val, *edge_value_);
}

template<class T>
std::string Edge<T>::Dot() const {
  std::stringstream out;

  out << "\"" << end_->name << "\"";
  out << " [label=\"  ";
  if(edge_value_) {
    out << *edge_value_;
  } else {
    out << "&#949;";
  }
  out << "\"]";

  return out.str();
}

template<class T>
template<class E, class O>
O Edge<T>::Transduce(E val, std::function<O (E,T)> output) const
{
  return output(val, *edge_value_);
}

template<class T>
bool Edge<T>::operator<(const Edge& other) const {
  return (end_ < other.end_) || 
         (end_ == other.end_ && edge_value_ < other.edge_value_);
}


#endif
