#include "init.h"
#include "scheduler.h"
#include "util.h"

void init_system() {
    log_message(LOG_INFO, "System initializing...");
    init_scheduler();
    log_message(LOG_INFO, "System initialized.");
}

