#include "scheduler.h"
#include "queue.h"
#include "process.h"
#include "util.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static process_queue_t ready_queue;
static process_t *current_process = NULL;

void init_scheduler() {
    init_queue(&ready_queue);
}

void schedule_process(process_t *p) {
    if (p && p->state == READY) {
        enqueue(&ready_queue, p);
    }
}

void start_scheduler() {
    while (1) {
        if (!is_queue_empty(&ready_queue)) {
            current_process = dequeue(&ready_queue);
            if (current_process) {
                run_process(current_process);
                if (current_process->state == TERMINATED) {
                    terminate_process(current_process);
                } else {
                    schedule_process(current_process);
                }
                current_process = NULL;
            }
        } else {
            break; // 준비 큐에 프로세스가 없으면 잠시 대기
        }
    }
}

void scheduler_tick() {
    if (current_process && current_process->state == RUNNING) {
        current_process->runtime++;
        if (current_process->runtime >= 3) { // 각 프로세스의 실행 시간 단위 (예: 3초)
            current_process->runtime = 0;
            current_process->state = READY;
            schedule_process(current_process);
            current_process = NULL;
        }
    }
    if (!current_process || current_process->state != RUNNING) {
        if (!is_queue_empty(&ready_queue)) {
            current_process = dequeue(&ready_queue);
            if (current_process) {
                run_process(current_process);
            }
        }
    }
}

