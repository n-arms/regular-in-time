#include "nodelist.h"
#include <string.h>

node_list new_node_list() {
  return (node_list) {
    .elems = NULL,
    .length = 0,
    .capacity = 0
  };
}

void free_node_list(node_list *list) {
  if (list->elems) free(list->elems);
  list->elems = NULL;
  list->length = 0;
  list->capacity = 0;
}

void push_to_node_list(node_list *list, size_t value) {
  if (list->capacity == 0) {
    list->elems = malloc(sizeof(size_t));
    *list->elems = value;
    list->length = 1;
    list->capacity = 1;
    return;
  }
  if (list->length == list->capacity) {
    size_t new_cap = list->capacity * 2;
    size_t *buffer = malloc(new_cap * sizeof(size_t));
    memcpy(buffer, list->elems, list->length*sizeof(size_t));
    free(list->elems);
    list->elems = buffer;
    list->capacity *= 2;
  }
  list->elems[list->length++] = value;
}

void sort_node_list(node_list *list) {
  if (list->length <= 1) return;

  for (size_t i = 1; i < list->length; ++i) {
    size_t elem = list->elems[i];
    for (size_t j = i; j > 0; --j) {
      size_t current = list->elems[j - 1];
      if (current > elem) {
        list->elems[j - 1] = elem;
        list->elems[j] = current;
      }
      elem = current;
    }
  }
}

void dedup_node_list(node_list *list) {
  size_t offset = 0;
  for (size_t i = 1; i < list->length; ++i) {
    if (list->elems[i] == list->elems[i - 1]) {
      offset += 1;
    } else {
      list->elems[i - offset] = list->elems[i];
    }
  }
  list->length -= offset;
}

size_t remove_node_list(node_list *list, size_t index) {
  if (index >= list->length) return -1;
  size_t value = list->elems[index];
  if (index == list->length-1) return value;

  memmove(list->elems+index, list->elems+index+1, list->length-index-1);

  list->length -= 1;
}
