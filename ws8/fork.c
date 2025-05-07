#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Your code here
    __pid_t id = fork(); // fork creates a new chile process 
    if (id ==0){
        fork();
    }


    
    printf("Hello dude\n");
    // if (id == 0 ){
    //     printf("Hello from child process \n");
    // } else {
    //     printf("Hello from the main process \n");
    // }
    return 0;
}