#include "syspro.h"
#include "process.h"
#include "scheduler.h"
#include "util.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h> // 문자열 처리를 위해 추가

void system_start() {
    log_message(LOG_INFO, "Starting system...");

    // 시스템 초기화
    init_system();

    // 타이머 초기화
    init_timer();

    // 스케줄러 실행
    start_scheduler();
}

pid_t sys_fork(void) {
    pid_t pid = fork();
    if (pid == 0) {
        log_message(LOG_INFO, "New child process created");
    } else if (pid > 0) {
        log_message(LOG_INFO, "Parent process returned from fork");
    } else {
        log_message(LOG_ERROR, "Fork failed");
    }
    return pid;
}

void sys_exit(int status) {
    log_message(LOG_INFO, "Exiting process with status %d", status);
    exit(status);
}

pid_t sys_wait(int *status) {
    pid_t pid = wait(status);
    if (pid != -1) {
        log_message(LOG_INFO, "Process %d exited with status %d", pid, *status);
    } else {
        log_message(LOG_ERROR, "Wait failed");
    }
    return pid;
}

int sys_kill(pid_t pid, int sig) {
    int result = kill(pid, sig);
    if (result == 0) {
        log_message(LOG_INFO, "Signal %d sent to process %d", sig, pid);
    } else {
        log_message(LOG_ERROR, "Failed to send signal %d to process %d", sig, pid);
    }
    return result;
}

pid_t sys_getpid(void) {
    pid_t pid = getpid();
    log_message(LOG_INFO, "Current process ID is %d", pid);
    return pid;
}

void *sys_sbrk(intptr_t increment) {
    void *old_brk = sbrk(increment);
    if (old_brk == (void *)-1) {
        log_message(LOG_ERROR, "sbrk failed to allocate memory");
    } else {
        log_message(LOG_INFO, "sbrk moved break from %p by %ld bytes", old_brk, (long)increment);
    }
    return old_brk;
}

unsigned int sys_sleep(unsigned int seconds) {
    unsigned int rem = sleep(seconds);
    if (rem == 0) {
        log_message(LOG_INFO, "Slept for %u seconds", seconds);
    } else {
        log_message(LOG_WARNING, "Sleep interrupted with %u seconds remaining", rem);
    }
    return rem;
}

void sys_update(void) {
    log_message(LOG_INFO, "System update routine called");
}

void system_shutdown() {
    log_message(LOG_INFO, "Shutting down system...");
    // 필요한 정리 작업 수행
    log_message(LOG_INFO, "System shutdown complete.");
}

