#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int uint;

#define TXTLEN 256 // Max size of a message sent from ground
#define CNTLEN 242 // message - 4 hashcode - 1 space - 8 timestamp - 1 space

typedef struct {
  uint hashcode : 16;
  uint timestamp : 32;
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
  uint idx;
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
void hash(Packet *, const TextBuffer *);
int validate(const Packet *, const TextBuffer *);

// Secrets
const TextBuffer *getUnipdSig();
const TextBuffer *getUnipdKey();

const TextBuffer *getOtherSig();
const TextBuffer *getOtherKey();

#endif // PROTOCOL
