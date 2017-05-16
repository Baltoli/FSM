#include <fsm/state.h>

#include <sstream>

std::string State::Dot() const
{
  std::stringstream out;

  out << "\"" << name << "\"";

  if(accepting) {
    out << " [shape=doublecircle]";
  }

  if(initial) {
    out << ";\"secret\" [style=invis,shape=point];\"secret\"->\"" << name << "\"";
  }

  return out.str();
}
