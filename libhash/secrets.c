#include <protocol.h>

const TextBuffer *getUnipdSig() {
  static const TextBuffer unipdsig = {
      .message =
          "##UNIPD_SIGNATURE_RSA#VNNAJSFBAJKCSANDJVNDCODBCASUOBDUBDOVBHFDB##"};
  return &unipdsig;
};
