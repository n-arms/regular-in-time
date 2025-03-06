#include "parse.h"
#include <stdlib.h>

bool parse_regex_list(parser *p, regex_list *out);

/// Parse any character.
bool parse_any(parser *p, char *out) {
  if (p->start == p->end) return false;
  *out = *(p->start++);
  return true;
}

/// Only accept the given letter.
bool parse_letter(parser *p, char l) {
  parser old = *p;
  char out;
  if (!parse_any(p, &out)) {
    *p = old;
    return false;
  }
  return out == l;
}

/// Only accept a character that the predicate returns true for.
bool parse_if(parser *p, bool (*predicate)(char), char *out) {
  if (!parse_any(p, out)) return false;
  return predicate(*out);
}

bool parse_single_regex(parser *p, regex *out) {
  char start;
  if (!parse_any(p, &start)) return false;
  if (start == '[') {
    regex_list list;
    if (!parse_regex_list(p, &list)) return false;
    out->tag = regex_tag_or;
    out->value.or = list;
    return parse_letter(p, ']');
  } else if (start == '(') {
    if (!parse_regex(p, out)) return false;
    return parse_letter(p, ')');
  } else {
    out->tag = regex_tag_character;
    out->value.character = start;

    while (parse_letter(p, '*')) {
      regex inner = *out;
      out->tag = regex_tag_many;
      out->value.many = malloc(sizeof(regex));
      *out->value.many = inner;
    }

    return true;
  }
}

bool parse_regex_list(parser *p, regex_list *out) {
  regex buf[1024];
  size_t index = 0;
  regex temp;

  while (parse_single_regex(p, &temp)) {
    buf[index++] = temp;
  }

  *out = new_regex_list(index);

  for (size_t i = 0; i < index; ++i) {
    out->elems[i] = buf[i];
  }

  return true;
}

bool parse_regex(parser *p, regex *out) {
  regex_list list;
  if (!parse_regex_list(p, &list)) return false;

  if (list.size == 1) {
    *out = list.elems[0];
    free(list.elems);
    return true;
  } else {
    out->tag = regex_tag_and;
    out->value.and = list;
    return true;
  }
}
