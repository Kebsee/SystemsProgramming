#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void secret() {
    setreuid(geteuid(), getegid());
    system("/bin/cat /home/q3/secret");
}

void lose() {
    printf("Try again...\n");
}

int main(int argc, char **argv) {
    // fp is function pointer
    struct {
        char buffer[1024];
        volatile unsigned int (*fp)();
    } locals;

    locals.fp = &lose;

    if (argc != 2) {
        printf("Usage: %s <some string>\n", argv[0]);
        return -1;
    }

    strcpy(locals.buffer, argv[1]);
    printf("Jumping to function at 0x%08x!!\n", (unsigned int)locals.fp);
    locals.fp();
    return 0;
}