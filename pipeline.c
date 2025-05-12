#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_LINE 256
#define MAX_CMDS 100

int main() {
    char line[MAX_LINE];
    char *commands[MAX_CMDS];
    int cmd_count = 0;

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) {
            continue;
        }
        commands[cmd_count] = strdup(line);
        cmd_count++;
    }

    int prev_pipe[2];
    for (int i = 0; i < cmd_count; i++) {
        int new_pipe[2];
        if (i < cmd_count - 1) {
            if (pipe(new_pipe) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (i > 0) {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            if (i < cmd_count - 1) {
                dup2(new_pipe[1], STDOUT_FILENO);
                close(new_pipe[0]);
                close(new_pipe[1]);
            }

            char *args[MAX_ARGS + 1];
            int j = 0;
            char *token = strtok(commands[i], " ");
            while (token != NULL && j < MAX_ARGS) {
                args[j++] = token;
                token = strtok(NULL, " ");
            }
            args[j] = NULL;

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            if (i > 0) {
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            if (i < cmd_count - 1) {
                prev_pipe[0] = new_pipe[0];
                prev_pipe[1] = new_pipe[1];
            }
            wait(NULL);
        }
    }

    return 0;
}