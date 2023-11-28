#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARG 10
#define MAXLINE 100

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    char *token;
    char *saveptr;
    int background;

    while (1) {
        // Step 1: Give a prompt and receive a command as input
        printf("Pls input cmd :  ");
        fgets(line, MAXLINE, stdin);

        // Remove the newline character from the input
        line[strcspn(line, "\n")] = '\0';

        // Step 2: Separate the command into command line arguments
        token = strtok_r(line, " ", &saveptr);
        int arg_count = 0;

        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;

            // Check for the background execution symbol "&"
            if (strcmp(token, "&") == 0) {
                background = 1;
                args[arg_count - 1] = NULL; // Set the last argument to NULL for execvp
                break;
            }

            token = strtok_r(NULL, " ", &saveptr);
        }

        // Set the last argument to NULL for execvp
        args[arg_count] = NULL;

        // Step 3: Create a child process and execute commands
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("Execvp error");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            // Step 4: Wait for the child process to finish
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }

        // Step 5: Return to step 1 and repeat the process
    }

    return 0;
}
