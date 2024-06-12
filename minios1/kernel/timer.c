#include "timer.h"
#include "scheduler.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h> // itimerval 구조체를 사용하기 위해 추가

void init_timer() {
    struct sigaction sa;
    struct itimerval timer;

    // 타이머 인터럽트 핸들러 설정
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Failed to setup signal handler");
    }

    // 타이머 설정: 1초 후 시작, 이후 매 1초마다 반복
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Failed to start timer");
    }
}

