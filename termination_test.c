#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t pid;
    int status;

    printf("\n========================================\n");
    printf("     PROCESS TERMINATION TEST\n");
    printf("========================================\n");

    printf("\nParent process started.");
    printf("\nParent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0) {

        printf("\nERROR: Failed to create child process.\n");
        return 1;

    }

    if (pid == 0) {

        printf("\n----------------------------------------\n");
        printf("           CHILD PROCESS\n");
        printf("----------------------------------------\n");

        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("\nChild is performing its task...\n");

        sleep(3);

        printf("Child task completed.\n");
        printf("Child is terminating...\n");

        exit(0);

    } else {

        printf("\n----------------------------------------\n");
        printf("           PARENT PROCESS\n");
        printf("----------------------------------------\n");

        printf("Child created successfully.\n");
        printf("Child PID: %d\n", pid);

        printf("\nParent is waiting for child termination...\n");

        wait(&status);

        printf("\n========================================\n");
        printf("       TERMINATION DETECTED\n");
        printf("========================================\n");

        if (WIFEXITED(status)) {

            int exit_status = WEXITSTATUS(status);

            printf("Child PID       : %d\n", pid);
            printf("Termination     : NORMAL\n");
            printf("Exit Status     : %d\n", exit_status);

            if (exit_status == 0) {
                printf("Message         : Process completed successfully.\n");
            } else {
                printf("Message         : Process completed with an exit status.\n");
            }

        } else {

            printf("Child did not terminate normally.\n");

        }

        printf("========================================\n");
    }

    return 0;
}
