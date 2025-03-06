#ifndef PARSE_H_
#define PARSE_H_

#include <stdbool.h>
#include "regexpr.h"

typedef struct {
  char *start;
  char *end;
} parser;

bool parse_regex(parser *p, regex *out);

#endif
