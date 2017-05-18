#include "regex.h"

#include <iostream>

int main()
{
  auto r = concat(
    concat(
      character('a'),
      star(character('b'))
    ),
    alternate(
      character('c'),
      empty()
    )
  );

  std::cout << r.Deterministic().Relabeled().Dot() << '\n';
  std::string input("abbbc");
  std::cout << r.AcceptsSequence(std::begin(input), std::end(input)) << '\n';

  return 0;
}
