#include "critical_comm_task.h"
#include "../task_params.h"
#include <stdint.h>

struct task_params {
  uint8_t param;
};

void critical_comm_task() {
  while(1) {
    /* wait for urgent command, take actions */
  }
};
