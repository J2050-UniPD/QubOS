#include "rx_comm_task.h"
#include "../task_params.h"
#include <stdint.h>

struct task_params {
  uint8_t param;
};

void rx_comm_task() {
  while(1) {
    /* wait until a command is received, take actions */
  }
};
