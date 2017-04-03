#ifndef EDGE_H
#define EDGE_H

#include <optional>
#include <string>

#include "state.h"

template<class T>
class Edge {
public:
  Edge(std::shared_ptr<State> end) :
    end_(end), edge_value_(std::nullopt) {}

  Edge(std::shared_ptr<State> end, T val) :
    end_(end), edge_value_(val) {}

  std::shared_ptr<State> End() const {
    return end_;
  }

  template<class E>
  bool Accepts(E val, std::function<bool (E,T)>) const;

  bool Accepts(T val) const;

  bool IsEpsilon() const {
    return !edge_value_;
  }

  std::optional<T> Value() const {
    return edge_value_;
  }

  bool operator<(const Edge& other) const {
    return (end_ < other.end_) || 
           (end_ == other.end_ && edge_value_ < other.edge_value_);
  }

  std::string Dot() const;
private:
  std::shared_ptr<State> end_;
  std::optional<T> edge_value_;
};

#include "edge_impl.cc"

#endif
