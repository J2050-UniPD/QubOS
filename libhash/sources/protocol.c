#include <protocol.h>
#include <stdio.h>

int parsePacketToText(Packet *packet, TextBuffer *msg) {
  return sprintf(msg->message, "%04x %08x %s", packet->hashcode, packet->timestamp, packet->content.message) > 0;
}

int parseTextToPacket(TextBuffer *msg, Packet *packet) {
  static uint hashcode, timestamp, errcode;
  errcode = sscanf(msg->message, "%04x %8x %242[a-zA-Z0-9 ]s", &hashcode, &timestamp, packet->content.message);
  packet->hashcode = hashcode;
  packet->timestamp = timestamp;
  return errcode > 0;
}
