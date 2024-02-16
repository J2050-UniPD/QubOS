#include <protocol.h>
#include <stdio.h>

void parseMsgToPacket(Message * msg, Packet * packet){
  sscanf(msg->message, "%hx %x %[242]s",&(packet->hashcode),&(packet->timestamp),packet->content);
}
