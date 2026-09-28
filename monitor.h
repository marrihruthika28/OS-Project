#ifndef MONITOR_H
#define MONITOR_H

#include <sys/types.h>

int monitor_process(pid_t pid, int *exit_status);

void display_termination_result(pid_t pid, int exit_status);

#endif
