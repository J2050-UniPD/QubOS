#include "libcrypt.h"
#include "protocol.h"
#include <stdio.h>
#include <string.h>

size_t mod(int num, size_t div) {
  return num < 0 ? ((-num * div + num) % div) : (num % div);
}

size_t indexOf(char c) {
  if ('a' <= c && c <= 'z') {
    return (c - 'a');
  } else if ('A' <= c && c <= 'Z') {
    return 26 + (c - 'A');
  } else if ('0' <= c && c <= '9') {
    return 26 + 26 + (c - '0');
  } else {
    return 26 + 26 + 10;
  }
}

#define ALPHALEN 63
void vigener(Message *msg, char *key, enum Mode mode) {
  static const char alphabet[ALPHALEN] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
  size_t keylen = strlen(key), idx, offset;
  for (size_t i = 0; i < MSGLEN && msg->message[i] != '\0'; i++) {
    idx = indexOf(msg->message[i]);
    offset = mode * indexOf(key[mod(i, keylen)]);
    msg->message[i] = alphabet[mod(idx + offset, ALPHALEN)];
  }
}