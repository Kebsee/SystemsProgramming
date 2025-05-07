#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {x
        perror("Error opening file");
        return 1;
    }

    const char *text = "Hello, World!\n";
    if (write(fd, text, 14) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}