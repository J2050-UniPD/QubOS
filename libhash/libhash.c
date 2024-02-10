#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rope.h"

char *getUnipdSig();

void print_rope(Rope *rope) {
  for (RopeIterator i = begin(rope); hasNext(&i); next(&i)) {
    printf("%c", get(&i));
  }
}

uint32_t djb2(Rope *str) {
  uint32_t digest = 5381;
  for (RopeIterator i = begin(str); hasNext(&i); next(&i)) {
    digest = ((digest << 5) + digest) + get(&i); // digest * 33 + get(&i);
  }
  return digest;
}

uint16_t sysv(uint32_t somma) {
  uint32_t dueSedici = 65536;         // 2 ** 16
  uint64_t dueTrentadue = 4294967296; // 2 ** 32
  uint16_t digest = (somma % dueSedici) + ((somma % dueTrentadue) / dueSedici);
  return (digest % dueSedici) + (digest / dueSedici);
}

void test(char *line) {
  Rope unipd = newRope(getUnipdSig(), NULL);
  Rope str = newRope(line, &unipd);

  printf("\n> ");
  print_rope(&str);
  printf("\n");
  printf("> '%8x'\n", sysv(djb2(&str)));
  printf("\n");
}

int main() {
  test("ciao mamma");
  test("andakjsnfkedjnfskdgjnsdfks");
  test("AAAAAAAAAAAAAAAAAAAAaa");
  test("eeeeeeeeee");
  test("eeeeeeeeef");
  test("eeefeeeeee");
  test("eeefeeeeed");
  test("eeedeeeeef");
  return 0;
}
