#include <protocol.h>
#include <stdio.h>

uint assert(Message * m){
  int load = 0;
  for(; load + 8 < TXTLEN; load += (m->buffer[8+load].value == m->load[load].value));
  return load
  + ((((m->hashcode      >> (0)*8) & 0xff) == m->buffer[0].value))
  + ((((m->hashcode      >> (1)*8) & 0xff) == m->buffer[1].value))
  + ((((m->hashcode      >> (2)*8) & 0xff) == m->buffer[2].value))
  + ((((m->hashcode      >> (3)*8) & 0xff) == m->buffer[3].value))
  + ((((m->timestamp     >> (0)*8) & 0xff) == m->buffer[4].value))
  + ((((m->timestamp     >> (1)*8) & 0xff) == m->buffer[5].value))
  + ((((m->timestamp     >> (2)*8) & 0xff) == m->buffer[6].value))
  + ((((m->timestamp     >> (3)*8) & 0xff) == m->buffer[7].value))
  ;
}

void p(int bool, char * msg){
  printf("[%s] :: %s \n", bool ? "OK" : "ER", msg);
}

int main(int argc, char **argv) {
  Message m = {};
  m.hashcode = 0x87654321;
  m.timestamp = 0x01020304;
  for(int i = 0; i + 8 < TXTLEN; m.load[i++].value = 0);

  int assertGen, assertHash, assertTime, assertBuff;
  assertGen  = assert(&m);

  m.hashcode = 0x1312141;
  assertHash = assert(&m); 

  m.timestamp = 0xdeadbeef;
  assertTime = assert(&m);

  m.buffer[0].value = 7;
  m.buffer[1].value = 2;
  m.buffer[2].value = 3;
  m.buffer[6].value = 1;
  m.buffer[7].value = 0;
  m.buffer[16+1].value = 2+37;
  m.buffer[16+2].value = 3+37;
  m.buffer[16+6].value = 1+37;
  m.buffer[16+7].value = 0+37;
  assertBuff = assert(&m);

  p(assertGen  == 256, "generazione");
  p(assertHash == 256, "modifica hashcode");
  p(assertTime == 256, "modifica hashcode");
  p(assertBuff == 256, "modifica hashcode");
}
