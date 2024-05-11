#include "comm_handler_task.h"
#include "../task_params.h"
#include <stdint.h>

struct task_params {
  uint8_t param;
};

void comm_handler_task() {
  while(1) {
    /* wait for a command, take actions accordingly */
  }
};
