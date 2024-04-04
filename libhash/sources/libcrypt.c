#include <protocol.h>

void vigenere(Message *msg, const Message *key, enum Mode mode) {
  for (u32 i = 0; i < sizeof(msg->buffer); i++) {
    msg->buffer[i] = msg->buffer[i] + mode * key->buffer[i];
  }
}
