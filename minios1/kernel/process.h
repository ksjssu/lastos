#ifndef PROCESS_H
#define PROCESS_H

typedef enum {
    READY,
    RUNNING,
    TERMINATED
} process_state_t;

typedef struct process {
    int id;
    char name[32];
    int priority;
    process_state_t state;
    int runtime; // 프로세스의 총 실행 시간
} process_t;

process_t* create_process(const char *name, int priority);
void run_process(process_t *p);
void terminate_process(process_t *p);
process_t* find_process_by_pid(int pid);
void release_process(process_t *p);

#endif // PROCESS_H

