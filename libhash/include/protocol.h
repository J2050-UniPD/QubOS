#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int uint;

#define TXTLEN 256 // Max size of a message sent from ground

typedef struct {
  char message[TXTLEN];
} TextBuffer;

typedef struct {
  uint hashcode : 16;
  uint timestamp : 32;
  TextBuffer content;
} Packet;

// Dynamic String allocation
typedef struct Rope Rope;
struct Rope {
  const TextBuffer *str;
  Rope *next;
};

typedef struct {
  Rope *rope;
  uint idx;
} RopeIterator;

RopeIterator RopeIterator_begin(Rope *rope);
char         RopeIterator_get(RopeIterator *i);
int          RopeIterator_hasNext(RopeIterator *i);
int          RopeIterator_next(RopeIterator *i);

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
