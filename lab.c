#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/lab.h"
#include "../include/ui.h"


void display_lab_menu(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                 PROCESS LABORATORY                         \n");
    printf("============================================================\n");

    printf("\n");
    printf("  1. Normal Process Termination\n");
    printf("  2. Custom Exit Status\n");
    printf("  3. Multiple Child Processes\n");
    printf("  4. wait() Synchronization\n");
    printf("  5. waitpid() Specific Child\n");
    printf("  0. Back to Main Menu\n");

    printf("\n============================================================\n");
}


void lab_normal_termination(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("              NORMAL TERMINATION EXPERIMENT                 \n");
    printf("============================================================\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        printf("\n[CHILD]\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());

        printf("\nChild is performing its task...\n");

        sleep(2);

        printf("Child completed its task.\n");
        printf("Child exiting normally with status 0.\n");

        exit(0);
    }

    int status;

    printf("\n[PARENT]\n");
    printf("Parent PID : %d\n", getpid());
    printf("Child PID  : %d\n", pid);

    waitpid(pid, &status, 0);

    printf("\n[RESULT]\n");

    if (WIFEXITED(status))
    {
        printf("Termination : NORMAL\n");
        printf("Exit Status : %d\n", WEXITSTATUS(status));
    }

    printf("\nExperiment completed.\n");
}


void lab_custom_exit_status(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                CUSTOM EXIT STATUS                          \n");
    printf("============================================================\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        printf("\n[CHILD]\n");
        printf("PID : %d\n", getpid());

        printf("Child will exit with status 7.\n");

        sleep(2);

        exit(7);
    }

    int status;

    printf("\n[PARENT]\n");
    printf("Waiting for child PID %d...\n", pid);

    waitpid(pid, &status, 0);

    printf("\n[RESULT]\n");

    if (WIFEXITED(status))
    {
        printf("Termination : NORMAL\n");
        printf("Exit Status : %d\n", WEXITSTATUS(status));
    }

    printf("\nThis demonstrates how a parent receives\n");
    printf("the exit status returned by a child.\n");
}


void lab_multiple_children(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("              MULTIPLE CHILD PROCESSES                      \n");
    printf("============================================================\n");

    pid_t children[3];

    for (int i = 0; i < 3; i++)
    {
        children[i] = fork();

        if (children[i] < 0)
        {
            perror("fork");
            return;
        }

        if (children[i] == 0)
        {
            printf("\n[CHILD %d]\n", i + 1);
            printf("PID  : %d\n", getpid());
            printf("PPID : %d\n", getppid());

            sleep(2 + i);

            printf("Child %d exiting.\n", i + 1);

            exit(0);
        }
    }

    printf("\n[PARENT]\n");
    printf("Created 3 child processes.\n");

    for (int i = 0; i < 3; i++)
    {
        int status;

        waitpid(children[i], &status, 0);

        printf("\nCollected Child %d\n", i + 1);
        printf("PID : %d\n", children[i]);

        if (WIFEXITED(status))
        {
            printf("Exit Status : %d\n",
                   WEXITSTATUS(status));
        }
    }

    printf("\nAll three children have been collected.\n");
}


void lab_wait_synchronization(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                 wait() SYNCHRONIZATION                     \n");
    printf("============================================================\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        printf("\n[CHILD]\n");
        printf("Child PID : %d\n", getpid());

        printf("Child working for 3 seconds...\n");

        sleep(3);

        printf("Child finished.\n");

        exit(0);
    }

    printf("\n[PARENT]\n");
    printf("Parent PID : %d\n", getpid());
    printf("Child PID  : %d\n", pid);

    printf("\nParent is now waiting for the child...\n");

    wait(NULL);

    printf("\nParent resumed after child termination.\n");
    printf("This demonstrates process synchronization.\n");
}


void lab_waitpid_specific_child(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("               waitpid() SPECIFIC CHILD                     \n");
    printf("============================================================\n");

    pid_t child1 = fork();

    if (child1 < 0)
    {
        perror("fork");
        return;
    }

    if (child1 == 0)
    {
        printf("\n[CHILD 1]\n");
        printf("PID : %d\n", getpid());

        sleep(2);

        printf("Child 1 exiting.\n");

        exit(10);
    }

    pid_t child2 = fork();

    if (child2 < 0)
    {
        perror("fork");
        return;
    }

    if (child2 == 0)
    {
        printf("\n[CHILD 2]\n");
        printf("PID : %d\n", getpid());

        sleep(4);

        printf("Child 2 exiting.\n");

        exit(20);
    }

    printf("\n[PARENT]\n");
    printf("Child 1 PID : %d\n", child1);
    printf("Child 2 PID : %d\n", child2);

    printf("\nParent will specifically wait for Child 2.\n");

    int status;

    waitpid(child2, &status, 0);

    printf("\nChild 2 collected using waitpid().\n");

    if (WIFEXITED(status))
    {
        printf("Child 2 Exit Status : %d\n",
               WEXITSTATUS(status));
    }

    /*
     * Collect Child 1 afterwards.
     */
    waitpid(child1, &status, 0);

    printf("\nChild 1 also collected.\n");

    if (WIFEXITED(status))
    {
        printf("Child 1 Exit Status : %d\n",
               WEXITSTATUS(status));
    }

    printf("\nSpecific-child monitoring completed.\n");
}


void run_process_laboratory(void)
{
    int choice;

    do
    {
        clear_screen();

        display_lab_menu();

        choice = get_menu_choice();

        switch (choice)
        {
            case 1:
                clear_screen();
                lab_normal_termination();
                pause_screen();
                break;

            case 2:
                clear_screen();
                lab_custom_exit_status();
                pause_screen();
                break;

            case 3:
                clear_screen();
                lab_multiple_children();
                pause_screen();
                break;

            case 4:
                clear_screen();
                lab_wait_synchronization();
                pause_screen();
                break;

            case 5:
                clear_screen();
                lab_waitpid_specific_child();
                pause_screen();
                break;

            case 0:
                break;

            default:
                printf("\nInvalid laboratory option.\n");
                pause_screen();
        }

    } while (choice != 0);
}
