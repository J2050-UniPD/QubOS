#include "mx.h"
#include <stdint.h>

struct mx 
{
    uint8_t method;
    uint8_t peripheral;
    uint8_t attr; 

    union 
    {
      uint64_t val64;
    };
};

union pba 
{
  mx mex;
  uint8_t buffer[sizeof(mx)];
};



