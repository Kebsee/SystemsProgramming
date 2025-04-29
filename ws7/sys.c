#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Your code here


    // one after the other     
    system("du -sh");
    system("df -h");
    // Run the two commands in parallel using fork

    if (fork() == 0) {
        // Child process: run "du -sh"
        execlp("du", "du", "-sh", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        // Another child process: run "df -h"
        execlp("df", "df", "-h", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }

    // Parent process: wait for both children to finish
    wait(NULL);
    wait(NULL);
    return 0;
} 