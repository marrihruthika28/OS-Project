#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

#define MAX_PROCESSES 10

typedef enum
{
    PROCESS_CREATED,
    PROCESS_RUNNING,
    PROCESS_TERMINATED
} ProcessStatus;

typedef struct
{
    int id;
    pid_t pid;
    pid_t ppid;
    ProcessStatus status;
    int exit_status;
} ProcessInfo;

pid_t create_child_process(void);

void run_child_task(int task_id);

#endif
