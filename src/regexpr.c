#include "regexpr.h"

regex_list new_regex_list(size_t size) {
  regex *elems = malloc(size * sizeof(regex));

  return (regex_list) {
    .elems = elems,
    .size = size
  };
}

void free_regex(regex r) {
  switch (r.tag) {
  case regex_tag_and: {
      for (size_t i = 0; i < r.value.and.size; ++i) {
        free_regex(r.value.and.elems[i]);
      }
      break;
  }
  case regex_tag_or: {
      for (size_t i = 0; i < r.value.or.size; ++i) {
        free_regex(r.value.or.elems[i]);
      }
      break;
  }
  case regex_tag_many: {
      free_regex(*r.value.many);
      break;
  }
  case regex_tag_character: {
      break;
  }
  }
}

void print_regex(regex r) {
  switch (r.tag) {
  case regex_tag_and: {
      printf("(");
      for (size_t i = 0; i < r.value.and.size; ++i) {
        print_regex(r.value.and.elems[i]);
      }
      printf(")");
      break;
  }
  case regex_tag_or: {
      printf("[");
      for (size_t i = 0; i < r.value.or.size; ++i) {
        print_regex(r.value.or.elems[i]);
      }
      printf("]");
      break;
  }
  case regex_tag_many: {
      print_regex(*r.value.many);
      printf("*");
      break;
  }
  case regex_tag_character: {
      printf("%c", r.value.character);
      break;
  }
  }
}
