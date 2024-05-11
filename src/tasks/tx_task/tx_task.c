#include "tx_task.h"
#include "../task_params.h"
#include <stdint.h>

struct task_params {
  uint8_t param;
};

void tx_task() {
  while(1) {
    /* transmit something */
  }
};
