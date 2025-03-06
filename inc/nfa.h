#ifndef NFA_H_
#define NFA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  char on_char;
  size_t next;
} nfa_edge;

typedef struct {
  nfa_edge *edges;
  size_t size;
} nfa_state;

typedef struct {
  nfa_state *states;
  size_t size;
  size_t start;
  size_t end;
} nfa;

/// Determine if the nfa matches a null-terminated string.
bool matches(nfa *nfa, char *str);

void free_nfa(nfa *nfa);
void free_nfa_state(nfa_state state);

#endif
