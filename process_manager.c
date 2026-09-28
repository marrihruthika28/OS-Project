#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../include/process_manager.h"
#include "../include/process.h"

void initialize_process_manager(ProcessManager *manager)
{
    manager->count = 0;

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        manager->processes[i].id = 0;
        manager->processes[i].pid = 0;
        manager->processes[i].ppid = 0;
        manager->processes[i].status = PROCESS_TERMINATED;
        manager->processes[i].exit_status = -1;
    }
}


int create_managed_process(ProcessManager *manager, int task_id)
{
    if (manager->count >= MAX_PROCESSES)
    {
        printf("ERROR: Maximum process limit reached.\n");
        return -1;
    }

    pid_t pid = create_child_process();

    if (pid < 0)
    {
        return -1;
    }

    if (pid == 0)
    {
        run_child_task(task_id);
    }

    ProcessInfo *process = &manager->processes[manager->count];

    process->id = manager->count + 1;
    process->pid = pid;
    process->ppid = getpid();
    process->status = PROCESS_RUNNING;
    process->exit_status = -1;

    manager->count++;

    return process->id;
}


void monitor_all_processes(ProcessManager *manager)
{
    printf("\n");
    printf("==============================================================\n");
    printf("                 PROCESS MONITORING                           \n");
    printf("==============================================================\n");

    printf("\nWaiting for all child processes to terminate...\n");

    for (int i = 0; i < manager->count; i++)
{
    /*
     * Skip processes that have already been collected.
     */
    if (manager->processes[i].status != PROCESS_RUNNING)
    {
        continue;
    }

    int status;

    pid_t result = waitpid(
        manager->processes[i].pid,
        &status,
        0
    );

        if (result == -1)
        {
            perror("waitpid");
            continue;
        }

        manager->processes[i].status = PROCESS_TERMINATED;

        if (WIFEXITED(status))
        {
            manager->processes[i].exit_status =
                WEXITSTATUS(status);
        }
        else
        {
            manager->processes[i].exit_status = -1;
        }

        printf("\n------------------------------------------\n");
        printf("TERMINATION EVENT\n");
        printf("------------------------------------------\n");

        printf("Process ID   : %d\n",
               manager->processes[i].id);

        printf("PID          : %d\n",
               manager->processes[i].pid);

        printf("PPID         : %d\n",
               manager->processes[i].ppid);

        printf("Status       : TERMINATED\n");

        printf("Exit Status  : %d\n",
               manager->processes[i].exit_status);

        if (manager->processes[i].exit_status == 0)
        {
            printf("Message      : Process completed successfully.\n");
        }
        else
        {
            printf("Message      : Process completed with status %d.\n",
                   manager->processes[i].exit_status);
        }
    }

    printf("\n==============================================================\n");
    printf("             ALL PROCESSES COLLECTED                         \n");
    printf("==============================================================\n");
}


void display_process_table(const ProcessManager *manager)
{
    printf("\n");
    printf("==============================================================\n");
    printf("                    PROCESS TABLE                             \n");
    printf("==============================================================\n");

    printf("%-5s %-10s %-10s %-15s %-10s\n",
           "ID",
           "PID",
           "PPID",
           "STATUS",
           "EXIT");

    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < manager->count; i++)
    {
        const ProcessInfo *process = &manager->processes[i];

        const char *status;

        switch (process->status)
        {
            case PROCESS_CREATED:
                status = "CREATED";
                break;

            case PROCESS_RUNNING:
                status = "RUNNING";
                break;

            case PROCESS_TERMINATED:
                status = "TERMINATED";
                break;

            default:
                status = "UNKNOWN";
        }

        printf("%-5d %-10d %-10d %-15s %-10d\n",
               process->id,
               process->pid,
               process->ppid,
               status,
               process->exit_status);
    }

    printf("==============================================================\n");
}


int get_active_process_count(const ProcessManager *manager)
{
    int count = 0;

    for (int i = 0; i < manager->count; i++)
    {
        if (manager->processes[i].status == PROCESS_RUNNING)
        {
            count++;
        }
    }

    return count;
}


int get_terminated_process_count(const ProcessManager *manager)
{
    int count = 0;

    for (int i = 0; i < manager->count; i++)
    {
        if (manager->processes[i].status == PROCESS_TERMINATED)
        {
            count++;
        }
    }

    return count;
}
void display_process_tree(const ProcessManager *manager)
{
    if (manager->count == 0)
    {
        printf("\nNo processes available.\n");
        return;
    }

    pid_t parent_pid = manager->processes[0].ppid;

    printf("\n");
    printf("==============================================================\n");
    printf("                     PROCESS TREE                             \n");
    printf("==============================================================\n");

    printf("\nPARENT PROCESS\n");
    printf("PID: %d\n", parent_pid);

    for (int i = 0; i < manager->count; i++)
    {
        const ProcessInfo *process =
            &manager->processes[i];

        if (i == manager->count - 1)
        {
            printf("\n└── CHILD %d\n", process->id);
        }
        else
        {
            printf("\n├── CHILD %d\n", process->id);
        }

        printf("    PID    : %d\n", process->pid);
        printf("    PPID   : %d\n", process->ppid);

        if (process->status == PROCESS_RUNNING)
        {
            printf("    STATUS : RUNNING\n");
        }
        else if (process->status == PROCESS_TERMINATED)
        {
            printf("    STATUS : TERMINATED\n");
        }
        else
        {
            printf("    STATUS : CREATED\n");
        }

        printf("    EXIT   : %d\n",
               process->exit_status);
    }

    printf("\n==============================================================\n");
}
