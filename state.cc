#include "state.h"

#include <sstream>

std::string State::Dot() const
{
  std::stringstream out;

  out << "\"" << name << "\"";

  if(accepting) {
    out << "[shape=doublecircle]";
  }

  if(initial) {
    out << ";\"secret\" [style=invis,shape=point];\"secret\"->\"" << name << "\"";
  }

  return out.str();
}

State State::Combined(std::set<std::shared_ptr<State>> states) 
{
  auto state = State{};

  std::stringstream name;
  name << "{";

  auto i = 0;
  for(auto it = states.begin(); it != states.end(); i++, it++) {
    name << (*it)->name;
    if(i != states.size() - 1) {
      name << ", ";
    }
  }

  name << "}";
  state.name = name.str();

  state.accepting = std::any_of(states.begin(), states.end(),
    [=](auto st) {
      return st->accepting;
    }
  );

  state.initial = (states.size() == 1 && (*states.begin())->initial);

  return state;
}
