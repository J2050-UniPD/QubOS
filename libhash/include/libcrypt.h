#include "protocol.h"

#ifndef CRYPT
#define CRYPT

enum Mode { ENCRYPT = 1, DECRYPT = -1 };
void vigener(Message *msg, char *key, enum Mode mode);

#endif
