#include <protocol.h>
#include <stdio.h>

void parsePacketToText(Packet * packet, TextBuffer * msg){
  sprintf(msg->message, "%4hx %08x %s",packet->hashcode,packet->timestamp,packet->content.message);
}

void parseTextToPacket(TextBuffer * msg, Packet * packet){
  fprintf(stderr,"\nparseTextToPacket: YET TO IMPLEMENT\n");
  // sscanf(msg->message, "%hx %x %[242]s",&(packet->hashcode),&(packet->timestamp),packet->content);
}
