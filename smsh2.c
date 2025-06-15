#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "smsh.h"

#define DFL_PROMPT "> "

void setup();
int execute_pipe(char *cmd1[], char *cmd2[]);

int main() {
    char *cmdline, *prompt, **arglist;
    int result;
    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if (strchr(cmdline, '|')) { // Check for pipe
            char *cmd1 = strtok(cmdline, "|");
            char *cmd2 = strtok(NULL, "|");

            if (cmd1 && cmd2) {
                char **arglist1 = splitline(cmd1);
                char **arglist2 = splitline(cmd2);

                if (arglist1 && arglist2) {
                    result = execute_pipe(arglist1, arglist2);
                    freelist(arglist1);
                    freelist(arglist2);
                }
            }
        } else {
            if ((arglist = splitline(cmdline)) != NULL) {
                result = execute(arglist);
                freelist(arglist);
            }
        }
        free(cmdline);
    }
    return 0;
}

void setup() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int execute_pipe(char *cmd1[], char *cmd2[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    if ((pid1 = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (pid1 == 0) { // First child
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        perror("execvp");
        exit(1);
    }

    if ((pid2 = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (pid2 == 0) { // Second child
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]);
        execvp(cmd2[0], cmd2);
        perror("execvp");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}