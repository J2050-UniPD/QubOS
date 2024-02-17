#include <stdint.h>

#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int uint;

#define TXTLEN 256 // full message
#define CNTLEN                                                                 \
  242 // full message - 4 hashcode - 1 space - 8 timestamp - 1 space

typedef struct {
  uint16_t hashcode : 16;
  uint32_t timestamp : 32;
  char content[CNTLEN];
} Packet;

typedef struct {
  char message[TXTLEN];
} TextBuffer;

// Dynamic String allocation
typedef struct Rope Rope;
struct Rope {
  TextBuffer *str;
  Rope *next;
};

typedef struct {
  Rope *rope;
  uint8_t idx : 8;
} RopeIterator;

Rope newRope(TextBuffer *str, Rope *next);
RopeIterator RopeIt_begin(Rope *rope);
char RopeIt_get(RopeIterator *i);
int RopeIt_hasNext(RopeIterator *i);
void RopeIt_next(RopeIterator *i);

// Encryption
enum Mode { ENCRYPT = 1, DECRYPT = -1 };
void vigener(TextBuffer *msg, const TextBuffer *key, enum Mode mode);

// Hashing
uint32_t djb2(Rope *str);
uint16_t sysv(uint32_t somma);

// Secrets
const TextBuffer *getUnipdSig();
const TextBuffer *getUnipdKey();

const TextBuffer *getOtherSig();
const TextBuffer *getOtherKey();

#endif // PROTOCOL
