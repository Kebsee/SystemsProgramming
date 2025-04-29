#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char *args[100];                     
    int i = 0;
    char *token = strtok(argv[1], " ");  

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;                      

    execvp(args[0], args);               
    return 1;
}
