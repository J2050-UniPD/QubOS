#include <stdlib.h>

typedef struct Rope Rope;
typedef struct RopeIterator RopeIterator;

Rope newRope(char *str, Rope *next);

RopeIterator begin(Rope *rope);
char get(RopeIterator *i);
bool hasNext(RopeIterator *i);
void next(RopeIterator *i);

#ifndef ROPE
#define ROPE

struct Rope {
  char *str;
  size_t len;
  Rope *next;
};

struct RopeIterator {
  Rope *rope;
  size_t idx;
};

#endif // ROPE
