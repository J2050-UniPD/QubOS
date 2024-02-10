#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rope.h"

char *getUnipdSig();
uint32_t djb2(Rope *str);
uint16_t sysv(uint32_t somma);
bool verifyMessage(uint16_t digest, char *msg);

void print_rope(Rope *rope) {
  for (RopeIterator i = begin(rope); hasNext(&i); next(&i)) {
    printf("%c", get(&i));
  }
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
  bool a[] = {verifyMessage(0x2c29, "ciao mamma"),
              verifyMessage(0x60d9, "andakjsnfkedjnfskdgjnsdfks"),
              verifyMessage(0x6940, "AAAAAAAAAAAAAAAAAAAAaa"),
              verifyMessage(0xff08, "eeeeeeeeee"),
              verifyMessage(0x879a, "eeeeeeeeef"),
              verifyMessage(0xcce1, "eeefeeeeee"),
              verifyMessage(0x4450, "eeefeeeeed"),
              verifyMessage(0xb9c0, "eeedeeeeef")};

  for (int i = 0; i < 8; i++){
    printf("%d\n", a[i]);
  }
  return 0;
}
