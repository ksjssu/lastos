#ifndef TRAP_H
#define TRAP_H

void init_traps();
void default_trap_handler(int sig);
void child_termination_handler(int sig);

#endif // TRAP_H

