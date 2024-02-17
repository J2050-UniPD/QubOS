#include <protocol.h>

typedef union {
  struct {
    uint u16l : 16;
    uint u16m : 16;
  };
  uint u32i : 32;
} SysvNumber;

SysvNumber djb2(Rope *str) {
  SysvNumber digest = { .u32i = 5381};
  for (RopeIterator i = RopeIt_begin(str); RopeIt_hasNext(&i); RopeIt_next(&i)) {
    digest.u32i = (digest.u32i * 33) + RopeIt_get(&i);
  }
  return digest;
}

SysvNumber sysv(SysvNumber digest) {
  digest.u16l += digest.u16m;
  digest.u16l += digest.u16m;
  return digest;
}

void hash(Packet *pkg, const TextBuffer *sig) {
  Rope sigRope = {.str = sig, .next = (Rope *)0};
  Rope strRope = {.str = &(pkg->content), .next = &sigRope};
  pkg->hashcode = sysv(djb2(&strRope)).u16l;
}

int validate(const Packet *pkg, const TextBuffer *sig) {
  Rope sigRope = {.str = sig, .next = (Rope *)0};
  Rope strRope = {.str = &(pkg->content), .next = &sigRope};
  return pkg->hashcode == sysv(djb2(&strRope)).u16l;
}
