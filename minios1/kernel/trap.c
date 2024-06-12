#include "trap.h"
#include "scheduler.h"
#include "process.h" // process_t를 사용하기 위해 추가
#include "util.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> // WNOHANG을 사용하기 위해 추가

void init_traps() {
    signal(SIGCHLD, child_termination_handler);  // 자식 프로세스 종료 처리
    signal(SIGTERM, default_trap_handler);       // 종료 신호 처리
    signal(SIGINT, default_trap_handler);        // 인터럽트 신호 처리
}

void default_trap_handler(int sig) {
    log_message(LOG_WARNING, "Default trap handler called for signal %d", sig);
    if (sig == SIGTERM || sig == SIGINT) {
        system_shutdown();
        _exit(0); // 즉시 종료
    }
}

void child_termination_handler(int sig) {
    log_message(LOG_INFO, "Child termination handler called for signal %d", sig);
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        log_message(LOG_INFO, "Child process %d terminated with status %d", pid, WEXITSTATUS(status));
        process_t *proc = find_process_by_pid(pid); // PID로 프로세스 객체 찾기
        if (proc) {
            release_process(proc); // 프로세스 리소스 해제
        }
    }
}

