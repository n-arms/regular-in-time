#include "parse_test.h"
#include "parse.h"
#include "regexpr.h"
#include <assert.h>

void test_parser() {
  parser p;
  p.start = "([ab]c)*";
  p.end = p.start + 8;
  
  regex out;

  assert(parse_regex(&p, &out));

  assert(out.tag == regex_tag_many);

  regex inner = *out.value.many;

  assert(inner.tag == regex_tag_and);
  assert(inner.value.and.size == 2);

  regex x = inner.value.and.elems[0];
  regex y = inner.value.and.elems[1];

  assert(x.tag == regex_tag_or);
  assert(x.value.or.size == 2);

  regex a = x.value.or.elems[0];
  regex b = x.value.or.elems[1];

  assert(a.tag == regex_tag_character);
  assert(a.value.character == 'a');

  assert(b.tag == regex_tag_character);
  assert(b.value.character == 'b');

  assert(y.tag == regex_tag_character);
  assert(y.value.character == 'c');

  free_regex(out);
}
