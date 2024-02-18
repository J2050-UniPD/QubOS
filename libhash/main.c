#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <protocol.h>

void print_rope(Rope *rope) {
  for (RopeIterator i = RopeIterator_begin(rope); RopeIterator_hasNext(&i); (void)RopeIterator_next(&i)) {
    printf("%c", RopeIterator_get(&i));
  }
}

void print_textbuffer(TextBuffer *txt) {
  printf("TextBuffer{ '%s' }", txt->message);
}

void print_packet(Packet *pkg) {
  printf("Packet{ %8x, %8x,", pkg->hashcode, pkg->timestamp);
  print_textbuffer(&pkg->content);
  printf(" }");
}

Packet pkgs[8] = {
    {.hashcode = 0x60d9, .content = {.message = "andakjsnfkedjnfskdgjnsdfks"}},
    {.hashcode = 0x6940, .content = {.message = "AAAAAAAAAAAAAAAAAAAAaa"}},
    {.hashcode = 0xff08, .content = {.message = "eeeeeeeeee"}},
    {.hashcode = 0x879a, .content = {.message = "eeeeeeeeef"}},
    {.hashcode = 0xcce1, .content = {.message = "eeefeeeeee"}},
    {.hashcode = 0x4450, .content = {.message = "eeefeeeeed"}},
    {.hashcode = 0xb9c0, .content = {.message = "eeedeeeeef"}},
    {.hashcode = 0xd8e1, .content = {.message = "a b c d e"}},
};

typedef union {
  struct {
    uint u16bl : 16;
    uint u16bm : 16;
  };
  uint u32b : 32;
} SysvNumber;

SysvNumber djb2(Rope *str);
void test_djb2_rope();
void test_packets();

int main(int argc, char **argv) {
  test_djb2_rope();
  // test_packets();
  return 0;
}

unsigned int djb2_real(char *str) {
  unsigned int hash = 5381;
  char c;
  while (c = *str++) {
    hash = hash * 33 + c;
  }
  return hash;
}

void test_djb2_rope() {
  for (int i = 0; i < 8; i++) {
    Packet *p = &(pkgs[i]);
    char *str = malloc(sizeof(char) * 512);
    sprintf(str, "%s%s%c", p->content.message, getUnipdSig()->message, '\0');
    print_packet(p);
    printf("\n");
    hash(p, getUnipdSig());
    Rope u = {.str = getUnipdSig(), .next = NULL};
    Rope s = {.str = &(p->content), .next = &u};
    SysvNumber h = djb2(&s);

    printf("CStr: %x '%s'\n",djb2_real(str),str);
    printf("Rope: %x '",h.u32b);
    print_rope(&s);
    printf("'\n");

    printf("\n");
    printf("\n");
  }
}

void test_packets() {

  for (int i = 0; i < 8; i++) {
    Packet *p = &(pkgs[i]);
    print_packet(p);
    printf("\n");
    continue;
    print_packet(p);
    printf("\n");
    printf("is_valid : %d\n", validate(p, getUnipdSig()));
    hash(p, getUnipdSig());
    printf("%4x\n", p->hashcode);
    print_packet(p);
    printf("\n");
    printf("is_valid %d\n", validate(p, getUnipdSig()));
    printf("\n");
    printf("\n");
  }
}

