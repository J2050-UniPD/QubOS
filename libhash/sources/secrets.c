#include <protocol.h>

const TextBuffer *getUnipdSig() {
  static const TextBuffer sig = {
      .message =
          "##UNIPD_SIGNATURE_RSA#VNNAJSFBAJKCSANDJVNDCODBCASUOBDUBDOVBHFDB##"};
  return &sig;
};

const TextBuffer *getOtherSig() {
  static const TextBuffer sig = {
      .message =
          "##3RD_PARTY_SIGNATURE_RSA##"};
  return &sig;
};
