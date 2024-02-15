#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rope.h"

#ifndef HASH
#define HASH

uint32_t djb2(Rope *str);
uint16_t sysv(uint32_t somma);
bool verifyMessage(uint16_t digest, char *msg);
bool verify(char *msg);


#endif
