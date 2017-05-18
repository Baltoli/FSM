#ifndef REGEX_H
#define REGEX_H

#include <fsm/fsm.h>

using regex = FiniteStateMachine<char>;

regex empty();
regex character(char c);
regex star(regex r);
regex concat(regex f, regex s);
regex alternate(regex a, regex b);

#endif
