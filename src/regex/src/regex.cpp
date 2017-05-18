#include "regex.h"

regex empty()
{
  regex r;
  auto i = r.AddState();
  i->initial = true;

  auto a = r.AddState();
  a->accepting = true;

  r.AddEdge(i, a);
  return r;
}

regex character(char c)
{
  regex r;

  auto i = r.AddState();
  i->initial = true;

  auto a = r.AddState();
  a->accepting = true;

  r.AddEdge(i, a, c);
  return r;
}

regex star(regex r)
{
  r.InitialState()->accepting = true;

  for(auto&& a : r.AcceptingStates()) {
    r.AddEdge(a, r.InitialState());
  }

  return r;
}

regex concat(regex f, regex s)
{
  regex fs;
  fs.AddSubMachine(f);
  fs.AddSubMachine(s);

  for(auto&& a : f.AcceptingStates()) {
    a->accepting = false;
    fs.AddEdge(a, s.InitialState());
  }
  
  s.InitialState()->initial = false;

  return fs;
}

regex alternate(regex a, regex b)
{
  regex ab;
  ab.AddSubMachine(a);
  ab.AddSubMachine(b);

  auto i = ab.AddState();
  i->initial = true;

  auto acc = ab.AddState();
  acc->accepting = true;

  std::vector<regex *> rs{ &a, &b };
  for(auto&& r : rs) {
    ab.AddEdge(i, r->InitialState());
    r->InitialState()->initial = false;

    for(auto&& racc : r->AcceptingStates()) {
      ab.AddEdge(racc, acc);
      racc->accepting = false;
    }
  }

  return ab;
}
