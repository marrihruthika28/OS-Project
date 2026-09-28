#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    printf("Before fork()\n");

    pid_t pid = fork();

    if (pid < 0) {
        printf("Failed to create child process.\n");
        return 1;
    }

    if (pid == 0) {
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());
    }
    else {
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);
    }

    return 0;
}
