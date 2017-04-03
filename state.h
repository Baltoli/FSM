#ifndef STATE_H
#define STATE_H

#include <set>
#include <string>

struct State {
  State() {}

  State(std::string s) :
    name(s) {}

  std::string name = "";
  bool accepting = false;
  bool initial = false;

  std::string Dot() const;

  static State Combined(std::set<std::shared_ptr<State>> states);
};

#endif
