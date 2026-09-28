#ifndef HISTORY_H
#define HISTORY_H

#include <sys/types.h>

#define MAX_HISTORY 50

typedef struct
{
    int event_id;
    pid_t pid;
    pid_t ppid;
    int exit_status;
    char termination_type[20];
    char detection_method[20];
} TerminationEvent;

typedef struct
{
    TerminationEvent events[MAX_HISTORY];
    int count;
} History;

void initialize_history(History *history);

void add_termination_event(
    History *history,
    pid_t pid,
    pid_t ppid,
    int exit_status
);

void display_history(const History *history);

#endif
