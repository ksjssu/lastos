#include "process.h"
#include "scheduler.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int process_id_counter = 0;

process_t* create_process(const char *name, int priority) {
    process_t *p = (process_t *)malloc(sizeof(process_t));
    if (p) {
        p->id = process_id_counter++;
        snprintf(p->name, sizeof(p->name), "%s%d", name, p->id);
        p->priority = priority;
        p->state = READY;
        p->runtime = 0; // 초기 실행 시간 설정
        log_message(LOG_INFO, "Process created: ID=%d, Name=%s, Priority=%d", p->id, p->name, p->priority);
    }
    return p;
}

void run_process(process_t *p) {
    if (p && p->state == READY) {
        log_message(LOG_INFO, "Running process: ID=%d, Name=%s", p->id, p->name);
        p->state = RUNNING;
        
        // 간단한 작업을 수행하고 종료
        sleep(1); // 작업 시뮬레이션
        
        p->state = TERMINATED;
        log_message(LOG_INFO, "Process terminated: ID=%d, Name=%s", p->id, p->name);
    }
}

void terminate_process(process_t *p) {
    if (p) {
        log_message(LOG_INFO, "Terminating process: ID=%d, Name=%s", p->id, p->name);
        p->state = TERMINATED;
        free(p);
    }
}

process_t *find_process_by_pid(int pid) {
    // 실제 구현에서는 프로세스 리스트를 검색해야 합니다.
    return NULL;
}

void release_process(process_t *p) {
    terminate_process(p);
}

