#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rope.h"

Rope newRope(char *str, Rope *next) {
  Rope tmp = {.str = str, .len = strlen(str), .next = next};
  return tmp;
}

RopeIterator begin(Rope *rope) {
  RopeIterator tmp = {.rope = rope, .idx = 0};
  return tmp;
}

char get(RopeIterator *i) { return i->rope->str[i->idx]; }

bool hasNext(RopeIterator *i) {
  return i->rope != NULL && (i->idx < i->rope->len || i->rope->next != NULL);
}

void next(RopeIterator *i) {
  if (i->rope == NULL) {
    perror("corda invalida");
    EXIT_FAILURE;
  } else if (i->idx < i->rope->len - 1) {
    i->idx++;
  } else {
    i->idx = 0;
    i->rope = i->rope->next;
  }
}
