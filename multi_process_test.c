#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHILDREN 3

int main() {

    pid_t children[MAX_CHILDREN];
    int status;

    printf("\n");
    printf("==================================================\n");
    printf("           MULTI-PROCESS MONITOR TEST             \n");
    printf("==================================================\n");

    printf("\nParent PID: %d\n", getpid());

    /*
     * Create three child processes
     */

    for (int i = 0; i < MAX_CHILDREN; i++) {

        children[i] = fork();

        if (children[i] < 0) {
            printf("ERROR: Failed to create Child %d\n", i + 1);
            return 1;
        }

        if (children[i] == 0) {

            printf("\n------------------------------------------\n");
            printf("CHILD %d CREATED\n", i + 1);
            printf("------------------------------------------\n");

            printf("PID  : %d\n", getpid());
            printf("PPID : %d\n", getppid());

            /*
             * Give each child a different workload
             */

            int work_time = (i + 1) * 2;

            printf("Status: RUNNING\n");
            printf("Working for %d seconds...\n", work_time);

            sleep(work_time);

            printf("Child %d completed its task.\n", i + 1);

            /*
             * Different exit statuses for demonstration
             */

            if (i == 0) {
                exit(0);
            }
            else if (i == 1) {
                exit(2);
            }
            else {
                exit(0);
            }
        }
    }

    /*
     * Parent process
     */

    printf("\n");
    printf("==================================================\n");
    printf("                PARENT MONITOR                    \n");
    printf("==================================================\n");

    printf("\nCreated %d child processes:\n", MAX_CHILDREN);

    for (int i = 0; i < MAX_CHILDREN; i++) {
        printf("Child %d → PID %d\n", i + 1, children[i]);
    }

    printf("\nMonitoring child processes...\n");

    /*
     * Wait for each specific child
     */

    for (int i = 0; i < MAX_CHILDREN; i++) {

        pid_t terminated_pid;

        terminated_pid = waitpid(children[i], &status, 0);

        printf("\n");
        printf("**********************************************\n");
        printf("          TERMINATION EVENT                  \n");
        printf("**********************************************\n");

        printf("Child PID      : %d\n", terminated_pid);

        if (WIFEXITED(status)) {

            int exit_status = WEXITSTATUS(status);

            printf("Termination    : NORMAL\n");
            printf("Exit Status    : %d\n", exit_status);

            if (exit_status == 0) {
                printf("Message        : Process completed successfully.\n");
            }
            else {
                printf("Message        : Process completed with status %d.\n",
                       exit_status);
            }

        }
        else {
            printf("Termination    : NOT NORMAL\n");
        }

        printf("**********************************************\n");
    }

    printf("\n");
    printf("==================================================\n");
    printf("             ALL PROCESSES COLLECTED              \n");
    printf("==================================================\n");

    printf("\nProcess monitoring completed successfully.\n");

    return 0;
}
