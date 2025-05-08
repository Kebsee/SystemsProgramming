#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 11     // 10 args + 1 NULL

int main() {
    char line[MAX_LINE_LENGTH];

    // while there are remaining commands:
    while (fgets(line, sizeof(line), stdin)) {
        // read line from stdin
        line[strcspn(line, "\n")] = '\0';  // remove newline

        // parse line into command and arguments
        char *argv[MAX_ARGS];
        int argc = 0;
        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;  // NULL-terminate the argument list

        // fork and handle errors
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        // if (child) execute command
        if (pid == 0) {
            execvp(argv[0], argv);
            perror("exec failed");
            exit(EXIT_FAILURE);
        }

        // else parent waits for child to terminate
        else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
