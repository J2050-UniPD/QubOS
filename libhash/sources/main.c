#include <protocol.h>
#include <stdio.h>

void print_buffersquare(u8 *b, u32 len) {
  for (u32 i = 0; i < len; i++) {
    if ((i % 32) == 0) {
      printf("\n\t\t");
    }
    if ((i % 8) == 0) {
      printf("  ");
    }
    printf("%02X", b[i]);
    printf(" ");
  }
  printf("\n");
}

void print_m(Message *m) {
  printf("Message {\n");
  printf("\tBuffer {");
  print_buffersquare(m->buffer, sizeof(m->buffer));
  printf("\t}\n");
  printf("\tPacket {\n");
  printf("\t\thashcode : %08X\n", m->hash);
  printf("\t\ttimestamp: %08X\n", m->time);
  printf("\t\tload {");
  print_buffersquare(m->load, sizeof(m->load));
  printf("\t\t}\n");
  printf("\t}\n");
  printf("}\n");
}

int main(int argc, char **argv) {
  Message m = {
    .hash = 0x12345678,
    .time = 0xdeadbeef,
    .load = "AAAAAAAABBBBBBBBCCCCCCCCCCCCCCCC"};
  print_m(&m);
  return 0;
}
