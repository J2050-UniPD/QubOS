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
    {.hashcode = 0x60d9, .timestamp = 0, .content = {.message = "andakjsnfkedjnfskdgjnsdfks"}},
    {.hashcode = 0x6940, .timestamp = 0, .content = {.message = "AAAAAAAAAAAAAAAAAAAAaa"}},
    {.hashcode = 0xff08, .timestamp = 0, .content = {.message = "eeeeeeeeee"}},
    {.hashcode = 0x879a, .timestamp = 0, .content = {.message = "eeeeeeeeef"}},
    {.hashcode = 0xcce1, .timestamp = 0, .content = {.message = "eeefeeeeee"}},
    {.hashcode = 0x4450, .timestamp = 0, .content = {.message = "eeefeeeeed"}},
    {.hashcode = 0xb9c0, .timestamp = 0, .content = {.message = "eeedeeeeef"}},
    {.hashcode = 0xd8e1, .timestamp = 0, .content = {.message = "a b c d e"}},
};

typedef union {
  struct {
    uint u16bl : 16;
    uint u16bm : 16;
  };
  uint u32b : 32;
} SysvNumber;

SysvNumber djb2(Rope *str);
SysvNumber sysv(SysvNumber);

unsigned int djb2_real(char *str) {
  unsigned int hash = 5381;
  char c;
  while (c = *str++) {
    hash = hash * 33 + c;
  }
  return hash;
}

unsigned short sysv_real(unsigned int sum){
  const int a = 65536;
  const long b = 4294967295;
  unsigned int r = (sum % a) + ((sum % b) / a);
  return (r % a) + (r / a);
}

int main(int argc, char **argv) {
  for (int i = 0; i < 8; i++) {
    Packet *p = &(pkgs[i]);
    char str[512];
    sprintf(str, "%s%s%c", p->content.message, getUnipdSig()->message, '\0');
    print_packet(p);
    printf("\n");
    hash(p, getUnipdSig());
    Rope u = {.str = getUnipdSig(), .next = NULL};
    Rope s = {.str = &(p->content), .next = &u};
    SysvNumber h = djb2(&s);

    printf("DJB2\n");
    printf("CStr: %x '%s'\n",djb2_real(str),str);
    printf("Rope: %x '",h.u32b);
    print_rope(&s);
    printf("'\n");

    printf("SYSV\n");
    printf("Real: %x -> %x\n",djb2_real(str), sysv_real(djb2_real(str)));
    printf("Unio: %x -> %x\n",h.u32b,sysv(h).u16bl);

    printf("VALIDATION\n");
    printf("unipd sig     : %d\n",validate(p, getUnipdSig()));
    printf("3rd party sig : %d\n",validate(p, getOtherSig()));

    // TODO : add timestamp to 
    printf("HASHING\n");
    printf("BEFORE : ");
    print_packet(p);
    printf("\n");
    hash(p, getUnipdSig());
    printf("AFTER  : ");
    print_packet(p);
    printf("\n");

    // TODO
    printf("PACKET TO TEXT\n");
    print_packet(p);
    printf("\n");
    printf("TEXT TO PACKET\n");
    Packet c = {.hashcode = 0, .timestamp = 0, .content = {.message = ""}};
    print_packet(&c);
    printf("\n");

    // TODO
    printf("ENCRYPTION\n");

    printf("\n");
    printf("\n");
  }
  return 0;
}
