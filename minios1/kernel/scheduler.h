#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void init_scheduler();
void schedule_process(process_t *p);
void start_scheduler();
void scheduler_tick();

#endif // SCHEDULER_H

