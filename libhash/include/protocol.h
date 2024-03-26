#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int uint;

// byte is strictly 8 bits
typedef struct {
  uint value : 8;
} byte;

// Max size of a message sent from ground
#define TXTLEN 256

typedef union {
  struct {
    byte buffer[TXTLEN];
  };
  struct {
    uint hashcode : 32;
    uint timestamp : 32;
    byte load[TXTLEN - 8];
  };
} Message;

//
// might delete later
//
typedef struct {
  byte buffer[TXTLEN];
} ByteBuffer;

typedef struct {
  uint hashcode : 32;
  uint timestamp : 32;
  ByteBuffer *load;
} Packet;


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

// Encryption
enum Mode { ENCRYPT = 1, DECRYPT = -1 };
void vigener(ByteBuffer *msg, const ByteBuffer *key, enum Mode mode);

// Hashing
void hash(Packet *, const ByteBuffer *);
int validate(const Packet *, const ByteBuffer *);

// Secrets
const ByteBuffer *getUnipdSig();
const ByteBuffer *getUnipdKey();

const ByteBuffer *getOtherSig();
const ByteBuffer *getOtherKey();

#endif // PROTOCOL
