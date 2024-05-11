#include "battery_task.h"
#include "../task_params.h"
#include <stdint.h>

struct task_params {
  uint8_t param;
};

void battery_task() {
  while(1) {
    /* listen to battery and according to its percetage, take actions */
  }
};
