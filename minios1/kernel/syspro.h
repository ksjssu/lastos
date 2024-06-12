#ifndef SYSPRO_H
#define SYSPRO_H

#include <sys/types.h>
#include <stdint.h> // intptr_t를 정의하기 위해 추가

void system_start();
pid_t sys_fork(void);
void sys_exit(int status);
pid_t sys_wait(int *status);
int sys_kill(pid_t pid, int sig);
pid_t sys_getpid(void);
void *sys_sbrk(intptr_t increment);
unsigned int sys_sleep(unsigned int seconds);
void sys_update(void);
void system_shutdown();

#endif // SYSPRO_H

