#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "process.h"

typedef struct
{
    ProcessInfo processes[MAX_PROCESSES];
    int count;
} ProcessManager;

void initialize_process_manager(ProcessManager *manager);

int create_managed_process(ProcessManager *manager, int task_id);

void display_process_table(const ProcessManager *manager);

int get_active_process_count(const ProcessManager *manager);

int get_terminated_process_count(const ProcessManager *manager);

void monitor_all_processes(ProcessManager *manager);
void display_process_tree(const ProcessManager *manager);
#endif
