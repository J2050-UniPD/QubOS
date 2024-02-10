#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rope.h"

char *getUnipdSig();

uint32_t djb2(Rope *str) {
  uint32_t digest = 5381;
  for (RopeIterator i = begin(str); hasNext(&i); next(&i)) {
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

bool verifyMessage(uint16_t digest, char *msg) {
  Rope unipd = newRope(getUnipdSig(), NULL);
  Rope msg_rope = newRope(msg, &unipd);
  return digest == sysv(djb2(&msg_rope));
}

bool verify(char * buffer){
  static uint16_t digest;
  static char content[256];
  sscanf(buffer,"%4x %255[^\n]",&digest,content);
  return verifyMessage(digest, content);
}
