#ifndef REGEXPR_H_
#define REGEXPR_H_

#include <stdlib.h>
#include <stdio.h>

struct regex;

typedef struct regex_list {
  struct regex *elems;
  size_t size;
} regex_list;

typedef union {
  regex_list and;
  regex_list or;
  struct regex *many;
  char character;
} regex_value;

typedef enum {
  regex_tag_and, regex_tag_or, regex_tag_many, regex_tag_character
} regex_tag;

typedef struct regex {
  regex_value value;
  regex_tag tag;
} regex;

regex_list new_regex_list(size_t size);
void free_regex(regex r);
void print_regex(regex r);

#endif
