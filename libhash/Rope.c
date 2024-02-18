#include <protocol.h>

RopeIterator RopeIterator_begin(Rope *rope) {
  RopeIterator tmp = {.rope = rope, .idx = 0};
  return tmp;
}

char RopeIterator_get(RopeIterator *i) { return i->rope->str->message[i->idx]; }

int RopeIterator_hasNext(RopeIterator *i) { return i->rope != (Rope *)0; }

int RopeIterator_next(RopeIterator *i) {
  if (i->rope == (Rope *)0) {
    return 0;
  }

  if (i->idx++ >= TXTLEN || RopeIterator_get(i) == '\0') {
    i->idx = 0;
    i->rope = i->rope->next;
  }

  return 1;
}
