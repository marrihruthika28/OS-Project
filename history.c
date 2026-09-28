#include <stdio.h>
#include <string.h>

#include "../include/history.h"

void initialize_history(History *history)
{
    history->count = 0;
}


void add_termination_event(
    History *history,
    pid_t pid,
    pid_t ppid,
    int exit_status
)
{
    if (history->count >= MAX_HISTORY)
    {
        return;
    }

    TerminationEvent *event =
        &history->events[history->count];

    event->event_id = history->count + 1;

    event->pid = pid;
    event->ppid = ppid;
    event->exit_status = exit_status;

    strcpy(event->termination_type, "NORMAL");
    strcpy(event->detection_method, "waitpid()");

    history->count++;
}


void display_history(const History *history)
{
    printf("\n");
    printf("==============================================================\n");
    printf("                  TERMINATION HISTORY                         \n");
    printf("==============================================================\n");

    if (history->count == 0)
    {
        printf("\nNo termination events recorded.\n");
        return;
    }

    printf("%-5s %-10s %-10s %-15s %-8s %-12s\n",
           "ID",
           "PID",
           "PPID",
           "STATUS",
           "EXIT",
           "DETECTION");

    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < history->count; i++)
    {
        const TerminationEvent *event =
            &history->events[i];

        printf("%-5d %-10d %-10d %-15s %-8d %-12s\n",
               event->event_id,
               event->pid,
               event->ppid,
               event->termination_type,
               event->exit_status,
               event->detection_method);
    }

    printf("==============================================================\n");
}
