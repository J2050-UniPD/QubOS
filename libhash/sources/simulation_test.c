#include <stdbool.h>
#include <stdio.h>

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
    printf("=======================================================================================================\n");
    printf("GROUND STATION\n");
    printf("\n");

    printf("Text to send\n");
    print_textbuffer(&msgs[i]);
    printf("\n");
    printf("\n");

    printf("Packaging\n");
    print_packet(&p);
    printf("\n");
    printf("\n");

    hash(&p, getUnipdSig());
    printf("Hashing\n");
    print_packet(&p);
    printf("\n");
    printf("\n");

    printf("Converting packet to text\n");
    TextBuffer toSend;
    parsePacketToText(&p, &toSend);
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
    if (i == 7) {
      toSend.message[0] = 'Z';
    }
    printf("\n");

    printf("\n");
    printf("SATELLITE\n");
    printf("\n");

    printf("Received text\n");
    print_textbuffer(&toSend);
    printf("\n");
    printf("\n");

    printf("Decryption\n");
    vigener(&toSend, getUnipdKey(), DECRYPT);
    print_textbuffer(&toSend);
    printf("\n");
    printf("\n");

    printf("Converting text to packet\n");
    Packet recv = {.hashcode = 0, .timestamp = 0, .content = {.message = ""}};
    if (parseTextToPacket(&toSend, &recv)) {
      printf("Error converting the text to packet\n");
    }
    print_packet(&recv);
    printf("\n");
    printf("\n");

    printf("Hash Validation\n");
    int isValid = validate(&recv, getUnipdSig());
    printf("Packet is %s valid and has been %s.\n", isValid ? "" : "NOT", isValid ? "ACCEPTED" : "DISCARDED");

    printf("\n");
  }
  return 0;
}
