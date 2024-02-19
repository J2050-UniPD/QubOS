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

void print_textbuffer(TextBuffer *txt) { printf("TextBuffer{ '%s' }", txt->message); }

void print_packet(Packet *pkg) {
  printf("Packet{ %8x, %8x,", pkg->hashcode, pkg->timestamp);
  print_textbuffer(&pkg->content);
  printf(" }");
}

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

unsigned short sysv_real(unsigned int sum) {
  const int a = 65536;
  const long b = 4294967295;
  unsigned int r = (sum % a) + ((sum % b) / a);
  return (r % a) + (r / a);
}

int main(int argc, char **argv) {
  TextBuffer msgs[8] = {
      {.message = "andakjsnfkedjnfskdgjnsdfks"},
      {.message = "AAAAAAAAAAAAAAAAAAAAaa"},
      {.message = "eeeeeeeeee"},
      {.message = "eeeeeeeeef"},
      {.message = "eeefeeeeee"},
      {.message = "eeefeeeeed"},
      {.message = "eeedeeeeef"},
      {.message = "a b c d e"},
  };

  for (int i = 0; i < 8; i++) {
    Packet p = {.hashcode = 0, .timestamp = i * 16, .content = msgs[i]};

    printf("\n");
    printf("===============================================================================================================\n");
    printf("GROUND STATION\n");
    printf("===============================================================================================================\n");
    printf("\n");

    printf("Hashing\n");
    printf("Original packet\n");
    print_packet(&p);
    printf("\n");
    hash(&p, getUnipdSig());
    printf("Hashed packet\n");
    print_packet(&p);
    printf("\n");

    printf("\n");
    printf("Converting packet to text\n");
    TextBuffer toSend;
    parsePacketToText(&p, &toSend);
    print_packet(&p);
    printf("\n");
    print_textbuffer(&toSend);
    printf("\n");

    printf("\n");
    printf("Encryption\n");
    vigener(&toSend, getUnipdKey(), ENCRYPT);
    print_textbuffer(&toSend);
    printf("\n");

    printf("\n");
    printf("\n");
    printf("Transmission\n");
    printf("\n");

    printf("\n");
    printf("SATELLITE\n");

    printf("\n");
    printf("Received text\n");
    print_textbuffer(&toSend);
    printf("\n");
    printf("Decryption\n");
    vigener(&toSend, getUnipdKey(), DECRYPT);
    print_textbuffer(&toSend);
    printf("\n");

    printf("\n");
    printf("Converting text to packet\n");
    print_textbuffer(&toSend);
    printf("\n");
    Packet recv;
    parseTextToPacket(&toSend, &recv);
    print_packet(&p);
    printf("\n");

    printf("Hash Validation\n");
    printf("Received packet\n");
    print_packet(&p);
    printf("\n");
    int isValid = validate(&p, getUnipdSig());
    if (isValid) {
      printf("Packet is valid\n");
    } else {
      printf("Packet was discarded\n");
    }

    printf("\n");
  }
  return 0;
}
