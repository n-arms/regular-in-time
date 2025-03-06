#include "nfa.h"
#include "nodelist.h"

/// Determine if the nfa matches a null-terminated string.
bool matches(nfa *nfa, char *str) {
  node_list nodes = new_node_list();
  push_to_node_list(&nodes, nfa->start);

  for (size_t i = 0; str[i] != '\0'; ++i) {
    for (size_t j = 0; j < nodes.length; ++j) {
      nfa_state state = nfa->states[j];
      for (size_t k = 0; k < state.size; ++k) {
        nfa_edge edge = state.edges[k];
        if (edge.on_char == '\0') {
          push_to_node_list(&nodes, edge.next);
        }
      }
    }

    node_list next_nodes = new_node_list();
    char c = str[i];

    for (size_t j = 0; j < nodes.length; ++j) {
      nfa_state state = nfa->states[j];
      for (size_t k = 0; k < state.size; ++k) {
        nfa_edge edge = state.edges[k];
        if (edge.on_char == c) {
          push_to_node_list(&next_nodes, edge.next);
        }
      }
    }

    free_node_list(&nodes);
    nodes = next_nodes;
  }

  for (size_t i = 0; i < nodes.length; ++i) {
    if (nodes.elems[i] == nfa->end) {
      free_node_list(&nodes);
      return true;
    }
  }

  free_node_list(&nodes);
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
