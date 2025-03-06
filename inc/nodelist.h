#ifndef NODELIST_H_
#define NODELIST_H_

#include <stdlib.h>

typedef struct {
  size_t *elems;
  size_t length;
  size_t capacity;
} node_list;

node_list new_node_list();
void push_to_node_list(node_list *list, size_t value);
void sort_node_list(node_list *list);
void dedup_node_list(node_list *list);
size_t remove_node_list(node_list *list, size_t index);

#endif
