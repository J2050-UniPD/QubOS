#ifndef PROTOCOL
#define PROTOCOL

#define MSGLEN 256

typedef struct Packet Packet;
typedef struct Message Message;

struct Packet {
  unsigned short hashcode;
  unsigned int timestamp;
  char content[MSGLEN - (sizeof(int) * 2) - (sizeof(short) * 2)];
};

struct Message {
  char message[MSGLEN];
};

#endif // PROTOCOL
