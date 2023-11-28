#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Start parent process\n");

    // Create three child processes
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Execute different commands based on the child process index
            switch (i) {
                case 0:
                    execl("/bin/echo", "echo", "hello", NULL);
                    perror("Exec failure");
                    exit(1);
                case 1:
                    execl("/bin/date", "date", NULL);
                    perror("Exec failure");
                    exit(2);
                case 2:
                    execl("/bin/ls", "ls", "-l", NULL);
                    perror("Exec failure");
                    exit(3);
                default:
                    // Should not reach here
                    exit(EXIT_FAILURE);
            }
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }

    printf("End of parent process\n");

    return 0;
}
