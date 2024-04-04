#include <protocol.h>

u32 djb2(u32 digest, const Message *m) {
  for (u32 i = sizeof(m->hash); i < sizeof(m->buffer); i++) {
    digest = digest * 33 + m->buffer[i];
  }
  return digest;
}

void hash(Message *pkg, const Message *sig) {
  pkg->hash = djb2(djb2(5381, sig), pkg);
}

u32 validate(const Message *pkg, const Message *sig){
  return pkg->hash == djb2(djb2(5381, sig), pkg);
}
