#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "smsh.h"

#define DFL_PROMPT "> "

void setup();
int execute_redirect(char *cmd[]);

int main() {
    char *cmdline, *prompt, **arglist;
    int result;
    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = splitline(cmdline)) != NULL) {
            result = execute_redirect(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

void setup() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int execute_redirect(char *cmd[]) {
    int fd, i;
    for (i = 0; cmd[i] != NULL; i++) {
        if (strcmp(cmd[i], ">") == 0) { // Output redirection
            cmd[i] = NULL;
            fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;
        } else if (strcmp(cmd[i], "<") == 0) { // Input redirection
            cmd[i] = NULL;
            fd = open(cmd[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;
        }
    }
    return execute(cmd);
}