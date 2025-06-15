#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <glob.h>
#include "smsh.h"

#define DFL_PROMPT "> "

void setup();
int execute_glob(char *cmd[]);

int main() {
    char *cmdline, *prompt, **arglist;
    int result;
    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = splitline(cmdline)) != NULL) {
            result = execute_glob(arglist);
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

int execute_glob(char *cmd[]) {
    glob_t globbuf;
    int i, glob_flags = 0;

    globbuf.gl_offs = 0;
    for (i = 0; cmd[i] != NULL; i++) {
        if (strchr(cmd[i], '*') || strchr(cmd[i], '?')) { // Detect wildcard
            glob(cmd[i], glob_flags, NULL, &globbuf);
            glob_flags = GLOB_APPEND;
        } else {
            globbuf.gl_pathv = realloc(globbuf.gl_pathv, sizeof(char *) * (globbuf.gl_pathc + 2));
            globbuf.gl_pathv[globbuf.gl_pathc++] = strdup(cmd[i]);
        }
    }
    globbuf.gl_pathv[globbuf.gl_pathc] = NULL;

    int result = execute(globbuf.gl_pathv);
    globfree(&globbuf);
    return result;
}