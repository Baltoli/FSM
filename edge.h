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

  template<class E>
  bool Accepts(E val, std::function<bool (E,T)>) const;

  bool IsEpsilon() const { return !edge_value_; }

  std::optional<T> Value() const { return edge_value_; }
  std::shared_ptr<State> End() const { return end_; }

  bool operator<(const Edge& other) const;

  std::string Dot() const;
private:
  std::shared_ptr<State> end_;
  std::optional<T> edge_value_;
};

#include "edge_impl.cc"

#endif
