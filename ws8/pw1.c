#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: redirect stdin and execute wc
        int fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            perror("open failed");
            return 1;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);

        execlp("wc", "wc", NULL); // Executes wc command
        perror("execlp failed"); // If exec fails
        return 1;
    } else {
        // Parent process: wait for the child to complete
        wait(NULL);
    }

    return 0;
}
