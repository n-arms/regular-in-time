#include "nfa.h"

/// Determine if the nfa matches a null-terminated string.
bool matches(nfa *nfa, char *str) {
  return false;
}

void free_nfa(nfa *nfa) {
  for (size_t i = 0; i < nfa->size; ++i) {
    free_nfa_state(nfa->states[i]);
  }
  free(nfa->states);
}

void free_nfa_state(nfa_state state) {
  free(state.edges);
}
