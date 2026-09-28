#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "../include/process.h"


pid_t create_child_process(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return -1;
    }

    return pid;
}

void run_child_task(int task_id)
{
    /*
     * Simulate a child process performing work.
     * The task ID makes each child distinguishable.
     */
    sleep(2 + task_id);

    /*
     * Exit normally.
     */
    exit(0);
}
