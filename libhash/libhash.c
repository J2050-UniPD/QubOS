#include <protocol.h>

typedef union {
  struct {
    uint u16bl : 16;
    uint u16bm : 16;
  };
  uint u32b : 32;
} SysvNumber;

SysvNumber djb2(Rope *str) {
  SysvNumber digest = { .u32b = 5381};
  for (RopeIterator i = RopeIterator_begin(str); RopeIterator_hasNext(&i); RopeIterator_next(&i)) {
    digest.u32b = (digest.u32b * 33) + RopeIterator_get(&i);
  }
  return digest;
}

SysvNumber sysv(SysvNumber digest) {
  digest.u32b  = digest.u16bl + digest.u16bm;
  digest.u16bl = digest.u16bl + digest.u16bm;
  return digest;
}

void hash(Packet *pkg, const TextBuffer *sig) {
  Rope sigRope = {.str = sig, .next = (Rope *)0};
  Rope strRope = {.str = &(pkg->content), .next = &sigRope};
  pkg->hashcode = sysv(djb2(&strRope)).u16bl;
}

int validate(const Packet *pkg, const TextBuffer *sig) {
  Rope sigRope = {.str = sig, .next = (Rope *)0};
  Rope strRope = {.str = &(pkg->content), .next = &sigRope};
  return pkg->hashcode == sysv(djb2(&strRope)).u16bl;
}
