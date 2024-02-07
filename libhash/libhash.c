#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getUnipdSig();

typedef struct Rope Rope;
struct Rope {
  char *str;
  size_t len;
  Rope *next;
};

typedef struct RopeIt RopeIt;
struct RopeIt {
  Rope *rope;
  size_t idx;
};

RopeIt begin(Rope *rope) {
  RopeIt tmp = {.rope = rope, .idx = 0};
  return tmp;
}

char get(RopeIt *i) { return i->rope->str[i->idx]; }

bool hasNext(RopeIt *i) {
  return i->rope != NULL && (i->idx < i->rope->len || i->rope->next != NULL);
}

void next(RopeIt *i) {
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

uint32_t djb2(Rope *str) {
  uint32_t digest = 5381;
  for (RopeIt i = begin(str); hasNext(&i); next(&i)) {
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
  char *unipdcstr = "##UNIPD_SIGNATURE_RSA#VNNAJSFBAJKCSANDJVNDCODBCASUOBDUBDOVBHFDB##";
  Rope unipd = {.str = unipdcstr, .len = strlen(unipdcstr), .next = NULL};
  Rope str = {.str = line, .len = strlen(line), .next = &unipd};

  printf("\n> ");
  for (RopeIt i = begin(&str); hasNext(&i); next(&i)) {
    printf("%c", get(&i));
  }
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
