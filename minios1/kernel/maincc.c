#include "trap.h"
#include "syspro.h"
#include "scheduler.h"
#include "init.h"
#include "process.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void create_and_run_command_process(const char *command) {
    process_t *p = create_process(command, 1);
    if (p) {
        if (fork() == 0) {
            if (strcmp(command, "makedir") == 0) {
                execlp("mkdir", "mkdir", "newdir", NULL);
            } else if (strcmp(command, "makefile") == 0) {
                execlp("touch", "touch", "newfile", NULL);
            } else if (strcmp(command, "readfile") == 0) {
                execlp("cat", "cat", "newfile", NULL);
            } else if (strcmp(command, "updatefile") == 0) {
                execlp("sh", "sh", "-c", "echo 'Updated content' > newfile", NULL);
            } else if (strcmp(command, "searchfile") == 0) {
                execlp("grep", "grep", "content", "newfile", NULL);
            } else if (strcmp(command, "print") == 0) {
                execlp("lp", "lp", "newfile", NULL);
            } else if (strcmp(command, "delete") == 0) {
                execlp("rm", "rm", "newfile", NULL);
            } else if (strcmp(command, "rename") == 0) {
                execlp("mv", "mv", "newfile", "renamedfile", NULL);
            } else if (strcmp(command, "copy") == 0) {
                execlp("cp", "cp", "newfile", "copyfile", NULL);
            } else if (strcmp(command, "dirsize") == 0) {
                execlp("du", "du", "-sh", "newdir", NULL);
            } else if (strcmp(command, "quit") == 0) {
                exit(0);
            } else {
                perror("Invalid command");
            }
            perror("execlp failed");
            exit(1);
        } else {
            schedule_process(p);
        }
    }
}

void initial_boot_process() {
    log_message(LOG_INFO, "Initial boot process running");
    // 부팅 과정에서 수행할 작업
    sleep(1); // 부팅 작업 시뮬레이션
    log_message(LOG_INFO, "Initial boot process completed");

    // 명령어 입력을 받아 프로세스 생성 및 실행
    char command[256];
    while (1) {
        printf("Enter a command to run (or 'exit' to quit): ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            continue;
        }
        command[strcspn(command, "\n")] = 0; // 개행 문자 제거

        if (strcmp(command, "exit") == 0) {
            break;
        } else {
            create_and_run_command_process(command);
        }
    }
    // 시스템 종료
    system_shutdown();
}

void maincc() {
    // 시스템 초기화
    system_start();

    // 인터럽트 핸들러 초기화
    init_traps();

    // 부팅 프로세스 생성 및 실행
    process_t *boot_process = create_process("BootProcess", 0);
    if (boot_process) {
        if (fork() == 0) {
            initial_boot_process();
            exit(0);
        } else {
            schedule_process(boot_process);
        }
    }

    // 스케줄러 시작
    start_scheduler();


}

