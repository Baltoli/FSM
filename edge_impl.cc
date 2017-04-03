#include <sstream>

template<class T>
template<class E>
bool Edge<T>::Accepts(E val, std::function<bool (E,T)> acceptor) const
{
  return edge_value_ && acceptor(val, *edge_value_);
}

template<class T>
bool Edge<T>::Accepts(T val) const
{
  return edge_value_ && val == *edge_value_;
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
