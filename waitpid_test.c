#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t child1;
    pid_t child2;
    int status;

    printf("\n============================================\n");
    printf("       WAITPID PROCESS MONITOR TEST\n");
    printf("============================================\n");

    printf("\nParent PID: %d\n", getpid());

    /* Create first child */
    child1 = fork();

    if (child1 < 0) {
        printf("ERROR: Failed to create Child 1.\n");
        return 1;
    }

    if (child1 == 0) {

        printf("\n[CHILD 1]\n");
        printf("PID: %d\n", getpid());
        printf("Child 1 is working...\n");

        sleep(3);

        printf("Child 1 terminating...\n");

        exit(0);
    }

    /* Create second child */
    child2 = fork();

    if (child2 < 0) {
        printf("ERROR: Failed to create Child 2.\n");
        return 1;
    }

    if (child2 == 0) {

        printf("\n[CHILD 2]\n");
        printf("PID: %d\n", getpid());
        printf("Child 2 is working...\n");

        sleep(5);

        printf("Child 2 terminating...\n");

        exit(0);
    }

    /* Parent process */

    printf("\n============================================\n");
    printf("             PARENT PROCESS\n");
    printf("============================================\n");

    printf("Child 1 PID: %d\n", child1);
    printf("Child 2 PID: %d\n", child2);

    printf("\nParent will monitor Child 2 specifically.\n");

    printf("\nWaiting for Child 2 using waitpid()...\n");

    waitpid(child2, &status, 0);

    printf("\n============================================\n");
    printf("       SPECIFIC CHILD TERMINATED\n");
    printf("============================================\n");

    printf("Child PID: %d\n", child2);

    if (WIFEXITED(status)) {

        printf("Termination : NORMAL\n");
        printf("Exit Status : %d\n", WEXITSTATUS(status));

    } else {

        printf("Termination : NOT NORMAL\n");
    }

    printf("\nChild 2 termination detected using waitpid().\n");

    /* Collect Child 1 */
    waitpid(child1, &status, 0);

    printf("\nChild 1 has also been collected.\n");

    printf("\n============================================\n");
    printf("             MONITOR COMPLETE\n");
    printf("============================================\n");

    return 0;
}
