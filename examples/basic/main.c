#include "regexpr.h"
#include "parse.h"
#include "nodelist.h"
#include <stdio.h>

int main() {
  node_list list = new_node_list();
  push_to_node_list(&list, 3);
  push_to_node_list(&list, 1);
  push_to_node_list(&list, 4);
  push_to_node_list(&list, 1);
  push_to_node_list(&list, 5);

  printf("after construction\n");
  for (size_t i = 0; i < list.length; ++i)
    printf("%lu\n", list.elems[i]);

  sort_node_list(&list);
  dedup_node_list(&list);

  printf("after sorting and duplication\n");
  for (size_t i = 0; i < list.length; ++i)
    printf("%lu\n", list.elems[i]);

  remove_node_list(&list, 2);

  printf("after removal\n");
  for (size_t i = 0; i < list.length; ++i)
    printf("%lu\n", list.elems[i]);

}
