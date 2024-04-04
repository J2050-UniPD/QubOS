#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int u32;
typedef unsigned char u8;

// byte is strictly 8 bits
typedef struct {
  u8 value : 8;
} byte;

// Max size of a message sent from ground
#define TXTLEN 256

typedef union {
  struct {
    byte buffer[TXTLEN];
  };
  struct {
    u32 hashcode : 32;
    u32 timestamp : 32;
    byte load[TXTLEN - 8];
  };
} Message;

// Encryption
enum Mode { ENCRYPT = 1, DECRYPT = -1 };
void vigener(ByteBuffer *msg, const ByteBuffer *key, enum Mode mode);

// Hashing
void hash(Packet *, const ByteBuffer *);
int validate(const Packet *, const ByteBuffer *);

// Dynamic String allocation
typedef struct Rope Rope;
struct Rope {
  const ByteBuffer *str;
  Rope *next;
};

typedef struct {
  Rope *rope;
  uint idx;
} RopeIterator;

RopeIterator RopeIterator_begin(Rope *rope);
char RopeIterator_get(RopeIterator *i);
int RopeIterator_hasNext(RopeIterator *i);
int RopeIterator_next(RopeIterator *i);

// Secrets
const ByteBuffer *getUnipdSig();
const ByteBuffer *getUnipdKey();

const ByteBuffer *getOtherSig();
const ByteBuffer *getOtherKey();

#endif // PROTOCOL
