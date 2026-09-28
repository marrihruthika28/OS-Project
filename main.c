#include <stdio.h>

#include "../include/ui.h"
#include "../include/process_manager.h"
#include "../include/history.h"
#include "../include/statistics.h"
#include "../include/dashboard.h"
#include "../include/lab.h"
int main(void)
{
    ProcessManager manager;
    History history;
    ProcessStatistics statistics;

    initialize_process_manager(&manager);
    initialize_history(&history);

    int choice;

    do
    {
        clear_screen();

        display_main_menu();

        choice = get_menu_choice();

        switch (choice)
        {
            case 1:
    init_dashboard();
    draw_dashboard();
    dashboard_menu();
    close_dashboard();
    break;

            case 2:
    clear_screen();

    printf("\n");
    printf("============================================================\n");
    printf("                  CREATE PROCESSES                          \n");
    printf("============================================================\n");

    if (manager.count > 0)
    {
        printf("\nA process group already exists.\n");

        printf("\nCurrent process count : %d\n",
               manager.count);

        printf("Active processes      : %d\n",
               get_active_process_count(&manager));

        printf("Terminated processes  : %d\n",
               get_terminated_process_count(&manager));

        printf("\nPlease monitor the existing processes before\n");
        printf("creating another process group.\n");
    }
    else
    {
        printf("\nCreating 3 child processes...\n");

        create_managed_process(&manager, 1);
        create_managed_process(&manager, 2);
        create_managed_process(&manager, 3);

        printf("\n3 child processes created successfully.\n");
    }

    pause_screen();
    break;


            case 3:
                clear_screen();

                printf("\n");
                printf("============================================================\n");
                printf("                LIVE PROCESS MONITOR                        \n");
                printf("============================================================\n");

                if (manager.count == 0)
                {
                    printf("\nNo processes have been created yet.\n");
                }
                else
                {
                    display_process_table(&manager);

                    printf("\nActive processes     : %d\n",
                           get_active_process_count(&manager));

                    printf("Terminated processes : %d\n",
                           get_terminated_process_count(&manager));
                }

                pause_screen();
                break;


            case 4:
                clear_screen();

                display_process_tree(&manager);

                pause_screen();
                break;


            case 5:
                clear_screen();

                display_history(&history);

                pause_screen();
                break;


            case 6:
                clear_screen();

                calculate_statistics(
                    &manager,
                    &history,
                    &statistics
                );

                display_statistics(&statistics);

                pause_screen();
                break;


            case 7:
    run_process_laboratory();
    break;

            case 8:
                clear_screen();

                printf("\n");
                printf("============================================================\n");
                printf("                       DEMO MODE                            \n");
                printf("============================================================\n");

                printf("\nRunning complete ProcessPulse demonstration...\n");

                if (manager.count == 0)
                {
                    printf("\nCreating demonstration processes...\n");

                    create_managed_process(&manager, 1);
                    create_managed_process(&manager, 2);
                    create_managed_process(&manager, 3);
                }

                monitor_all_processes(&manager);

                for (int i = 0; i < manager.count; i++)
                {
                    add_termination_event(
                        &history,
                        manager.processes[i].pid,
                        manager.processes[i].ppid,
                        manager.processes[i].exit_status
                    );
                }

                printf("\nDemonstration completed successfully.\n");

                pause_screen();
                break;


            case 9:
                clear_screen();

                printf("\n");
                printf("============================================================\n");
                printf("                     EXPLAIN MODE                           \n");
                printf("============================================================\n");

                printf("\nPROCESSPULSE OS CONCEPTS\n\n");

                printf("fork()\n");
                printf("Creates a new child process.\n\n");

                printf("exit()\n");
                printf("Terminates the current process and returns an exit status.\n\n");

                printf("wait()\n");
                printf("Allows a parent to wait for a child process to terminate.\n\n");

                printf("waitpid()\n");
                printf("Allows the parent to wait for and monitor a specific child.\n\n");

                printf("WIFEXITED()\n");
                printf("Checks whether a child terminated normally.\n\n");

                printf("WEXITSTATUS()\n");
                printf("Retrieves the child's exit status.\n");

                pause_screen();
                break;


            case 10:
                clear_screen();

                printf("\n");
                printf("============================================================\n");
                printf("                    ABOUT PROCESSPULSE                      \n");
                printf("============================================================\n");

                printf("\nProcessPulse\n");
                printf("Linux Process Termination Monitor\n\n");

                printf("Purpose:\n");
                printf("A practical Operating Systems tool for demonstrating\n");
                printf("process creation, termination, synchronization,\n");
                printf("monitoring and process relationships.\n\n");

                printf("Core Technologies:\n");
                printf("- C Programming\n");
                printf("- Linux Processes\n");
                printf("- fork()\n");
                printf("- wait()\n");
                printf("- waitpid()\n");
                printf("- exit()\n");
                printf("- Process IDs and Parent Process IDs\n");

                pause_screen();
                break;


            case 0:
                clear_screen();

                printf("\n");
                printf("============================================================\n");
                printf("             Thank you for using ProcessPulse               \n");
                printf("============================================================\n\n");

                break;


            default:
                printf("\nInvalid choice. Please select 0-10.\n");

                pause_screen();
        }

    } while (choice != 0);

    return 0;
}
