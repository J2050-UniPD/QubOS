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

/*
void test(char *line) {
  Rope unipd = newRope(getUnipdSig(), NULL);
  Rope str = newRope(line, &unipd);

  printf("\n> ");
  print_rope(&str);
  printf("\n");
  printf("> '%8x'\n", sysv(djb2(&str)));
  printf("\n");
}

void test_verifyMessage() {
  bool a[] = {verifyMessage(0x60d9, "andakjsnfkedjnfskdgjnsdfks"),
              verifyMessage(0x6940, "AAAAAAAAAAAAAAAAAAAAaa"),
              verifyMessage(0xff08, "eeeeeeeeee"),
              verifyMessage(0x879a, "eeeeeeeeef"),
              verifyMessage(0xcce1, "eeefeeeeee"),
              verifyMessage(0x4450, "eeefeeeeed"),
              verifyMessage(0xb9c0, "eeedeeeeef")};

  for (int i = 0; i < 8; i++) {
    printf("%d\n", a[i]);
  }
}

void test_verify() {
  bool a[] = {verify("60d9 andakjsnfkedjnfskdgjnsdfks"),
              verify("6940 AAAAAAAAAAAAAAAAAAAAaa"),
              verify("ff08 eeeeeeeeee"),
              verify("879a eeeeeeeeef"),
              verify("cce1 eeefeeeeee"),
              verify("4450 eeefeeeeed"),
              verify("b9c0 eeedeeeeef")};

  for (int i = 0; i < 8; i++) {
    printf("%d '%s' \n", a[i]);
  }
}

typedef struct tup tup;
struct tup {
  char *msg;
  uint16_t digest;
  bool v;
  bool v2;
};

#define len 8
void fast_test() {
  tup a[len] = {
      {.v = 0, .v2 = 0, .digest = 0x60d9, .msg = "andakjsnfkedjnfskdgjnsdfks"},
      {.v = 0, .v2 = 0, .digest = 0x6940, .msg = "AAAAAAAAAAAAAAAAAAAAaa"},
      {.v = 0, .v2 = 0, .digest = 0xff08, .msg = "eeeeeeeeee"},
      {.v = 0, .v2 = 0, .digest = 0x879a, .msg = "eeeeeeeeef"},
      {.v = 0, .v2 = 0, .digest = 0xcce1, .msg = "eeefeeeeee"},
      {.v = 0, .v2 = 0, .digest = 0x4450, .msg = "eeefeeeeed"},
      {.v = 0, .v2 = 0, .digest = 0xb9c0, .msg = "eeedeeeeef"},
      {.v = 0, .v2 = 0, .digest = 0xd8e1, .msg = "a b c d e"},
  };
  for (int i = 0; i < len; i++) {
    printf("'%s'\n", a[i].msg);

#define UNIPD
#ifdef UNIPD
    Rope unipd = newRope(getUnipdSig(), NULL);
    Rope str = newRope(a[i].msg, &unipd);
#else
    Rope str = newRope(a[i].msg, NULL);
#endif

    uint16_t calc_digest = sysv(djb2(&str));
    printf("digest: '%8x' '%8x' \n", calc_digest, a[i].digest);

    char buff[256];
    sprintf(buff, "%4x %s", calc_digest, a[i].msg);
    printf("'%s'\n", buff);
    uint16_t extracted_digest;
    char extracted_str[256];
    sscanf(buff, "%4x %255[^\n]s", &extracted_digest, extracted_str);
    printf("'%4x' '%s'\n", extracted_digest, extracted_str);
    printf("verify msg : %d\n", verifyMessage(extracted_digest, extracted_str));
    printf("verify : %d\n", verify(buff));
    printf("\n\n");
  }
}

#undef len

void vigener_test() {
  // Message msg = {.message = "ciao XYZ01 abcdevwxyz"};
  // char key[256] = "passwordsupersegreta";

  Message msg;
  char key[256] = "passwordsupersegreta";
  scanf("%255[a-zA-Z0-9 ]s|", msg.message);
  printf("password : '%s'\n\n", key);

  printf("msg      : '%s'\n", msg.message);
  vigener(&msg, key, ENCRYPT);
  printf("encrypt  : '%s'\n", msg.message);
  vigener(&msg, key, DECRYPT);
  printf("decrypt  : '%s'\n", msg.message);

  EXIT_SUCCESS;
}
*/

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

