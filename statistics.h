#ifndef STATISTICS_H
#define STATISTICS_H

#include "process_manager.h"
#include "history.h"

typedef struct
{
    int total_created;
    int currently_running;
    int terminated;
    int successful_exits;
    int non_zero_exits;
    int normal_terminations;
} ProcessStatistics;

void calculate_statistics(
    const ProcessManager *manager,
    const History *history,
    ProcessStatistics *statistics
);

void display_statistics(
    const ProcessStatistics *statistics
);

#endif
