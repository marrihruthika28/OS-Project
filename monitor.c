#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/monitor.h"

int monitor_process(pid_t pid, int *exit_status)
{
    int status;

    pid_t result = waitpid(pid, &status, 0);

    if (result == -1)
    {
        perror("waitpid");
        return -1;
    }

    if (WIFEXITED(status))
    {
        *exit_status = WEXITSTATUS(status);
        return 0;
    }

    *exit_status = -1;
    return 1;
}

void display_termination_result(pid_t pid, int exit_status)
{
    printf("\n============================================\n");
    printf("          TERMINATION DETECTED\n");
    printf("============================================\n");

    printf("Child PID       : %d\n", pid);
    printf("Termination     : NORMAL\n");
    printf("Exit Status     : %d\n", exit_status);

    if (exit_status == 0)
    {
        printf("Message         : Process completed successfully.\n");
    }
    else
    {
        printf("Message         : Process completed with status %d.\n",
               exit_status);
    }

    printf("============================================\n");
}
