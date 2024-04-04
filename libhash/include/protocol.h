#ifndef PROTOCOL
#define PROTOCOL

typedef unsigned int u32;
typedef unsigned char u8;

// Max size of a message sent from ground
#define TXTLEN 256

typedef union {
  struct {
    u8 buffer[TXTLEN];
  };
  struct {
    u32 hash;
    u32 time;
    u8 load[TXTLEN - 8];
  };
} Message;

// Encryption
enum Mode { ENCRYPT = 1, DECRYPT = -1 };
void vigener(Message *msg, const Message *key, enum Mode mode);

// Hashing
void hash(Message *, const Message *);
u32 validate(const Message *, const Message *);

// Secrets
const Message *getUnipdSig();
const Message *getUnipdKey();

const Message *getOtherSig();
const Message *getOtherKey();

#endif // PROTOCOL
