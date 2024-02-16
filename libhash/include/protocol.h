#ifndef PROTOCOL
#define PROTOCOL

#define MSGLEN 256 // full message
#define CNTLEN 242 // full message - 4 hashcode chars - 1 space - 8 timestamp chars - 1 space

typedef struct Packet Packet;
typedef struct Message Message;

struct Packet {
  unsigned short hashcode;
  unsigned int timestamp;
  char content[CNTLEN];
};

struct Message {
  char message[MSGLEN];
};

#endif // PROTOCOL
