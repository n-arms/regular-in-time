#include "nodelist_test.h"
#include "nodelist.h"
#include <assert.h>
#include <stdio.h>

void test_nodelist() {
  node_list list = new_node_list();
  push_to_node_list(&list, 3);
  push_to_node_list(&list, 1);
  push_to_node_list(&list, 4);
  push_to_node_list(&list, 1);
  push_to_node_list(&list, 5);

  assert(list.length == 5);
  assert(list.elems[0] == 3);
  assert(list.elems[1] == 1);
  assert(list.elems[2] == 4);
  assert(list.elems[3] == 1);
  assert(list.elems[4] == 5);

  sort_node_list(&list);
  dedup_node_list(&list);

  assert(list.length == 4);
  assert(list.elems[0] == 1);
  assert(list.elems[1] == 3);
  assert(list.elems[2] == 4);
  assert(list.elems[3] == 5);

  remove_node_list(&list, 2);

  assert(list.length == 3);
  assert(list.elems[0] == 1);
  assert(list.elems[1] == 3);
  assert(list.elems[2] == 5);

  free_node_list(&list);
}
