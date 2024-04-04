#include <protocol.h>

u32 assert(Message * m){
  u32 assertion = 0;
  for(u32 i = 0; i < sizeof(m->load); i++, assertion++);
  return assertion
  + ((((m->hash >> (0)*8) & 0xff) == m->buffer[0]))
  + ((((m->hash >> (1)*8) & 0xff) == m->buffer[1]))
  + ((((m->hash >> (2)*8) & 0xff) == m->buffer[2]))
  + ((((m->hash >> (3)*8) & 0xff) == m->buffer[3]))
  + ((((m->time >> (0)*8) & 0xff) == m->buffer[4]))
  + ((((m->time >> (1)*8) & 0xff) == m->buffer[5]))
  + ((((m->time >> (2)*8) & 0xff) == m->buffer[6]))
  + ((((m->time >> (3)*8) & 0xff) == m->buffer[7]))
  ;
}

void test_endianness(void) {
  Message m = {};
  m.hash = 0x87654321;
  m.time = 0x01020304;
  for(u32 i = 0; i < sizeof(m.load); m.load[i++] = 0);

  u32 assertGen, assertHash, assertTime, assertBuff;
  assertGen  = assert(&m);

  m.hash = 0x1312141;
  assertHash = assert(&m); 

  m.time = 0xdeadbeef;
  assertTime = assert(&m);

  m.buffer[0] = 7;
  m.buffer[1] = 2;
  m.buffer[2] = 3;
  m.buffer[6] = 1;
  m.buffer[7] = 0;
  m.buffer[16+1] = 2+37;
  m.buffer[16+2] = 3+37;
  m.buffer[16+6] = 1+37;
  m.buffer[16+7] = 0+37;
  assertBuff = assert(&m);

  if(
    assertGen  == 256 &&
    assertHash == 256 &&
    assertTime == 256 &&
    assertBuff == 256 
  ){
    // fai blinkare il led verde
  }else{
    // fai blinkare il led rosso
  }
}
