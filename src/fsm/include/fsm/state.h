/**
 * @file
 */
#ifndef FSM_STATE_H
#define FSM_STATE_H

#include <memory>
#include <set>
#include <string>

/**
 * Represents a single state in a finite state machine.
 */
struct State {
  /**
   * Construct a state whose name is the empty string.
   *
   * The constructed state is neither accepting nor initial.
   */
  State() {}

  /**
   * Construct a state with the given name.
   *
   * The constructed state is neither accepting nor initial.
   *
   * \param s The name assigned to the state
   */
  State(std::string s) :
    name(s) {}

  /**
   * Names a state for debugging output.
   */
  std::string name = "";

  /**
   * Does an FSM accept if it is in this state?
   */
  bool accepting = false;

  /**
   * Is this state the initial state of the FSM it belongs to?
   */
  bool initial = false;

  /**
   * Returns a DOT representation of this state.
   *
   * A string returned from this method can be placed in a GraphViz digraph in
   * order to print an entire FSM.
   *
   * \returns DOT formatted string representing the state
   */
  std::string Dot() const;

  /**
   * Construct a new state from a set of existing states.
   *
   * The resulting state has a name derived from the names of the passed states,
   * and derives its properties from these states as follows:
   * * If any of the passed states are accepting, the combined state is
   *   accepting.
   * * If there is exactly one state in the set (and it is initial), the new
   *   state is also initial.
   *
   * \param states A set of states to combine into a new state.
   * \returns A new state derived from the given set of states.
   */
  static State Combined(std::set<std::shared_ptr<State>> states);
};

#endif
