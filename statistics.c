#include <stdio.h>

#include "../include/statistics.h"

void calculate_statistics(
    const ProcessManager *manager,
    const History *history,
    ProcessStatistics *statistics
)
{
    statistics->total_created = manager->count;

    statistics->currently_running =
        get_active_process_count(manager);

    statistics->terminated =
        get_terminated_process_count(manager);

    statistics->successful_exits = 0;
    statistics->non_zero_exits = 0;
    statistics->normal_terminations = 0;

    for (int i = 0; i < history->count; i++)
    {
        if (history->events[i].exit_status == 0)
        {
            statistics->successful_exits++;
        }
        else
        {
            statistics->non_zero_exits++;
        }

        if (history->events[i].exit_status >= 0)
        {
            statistics->normal_terminations++;
        }
    }
}

void display_statistics(
    const ProcessStatistics *statistics
)
{
    printf("\n");
    printf("==================================================\n");
    printf("              PROCESS STATISTICS                  \n");
    printf("==================================================\n");

    printf("Total Created       : %d\n",
           statistics->total_created);

    printf("Currently Running   : %d\n",
           statistics->currently_running);

    printf("Terminated          : %d\n",
           statistics->terminated);

    printf("Successful Exits    : %d\n",
           statistics->successful_exits);

    printf("Non-Zero Exits      : %d\n",
           statistics->non_zero_exits);

    printf("Normal Terminations : %d\n",
           statistics->normal_terminations);

    printf("==================================================\n");
}
