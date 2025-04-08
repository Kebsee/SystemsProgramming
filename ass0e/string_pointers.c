#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Your code here
    char str[100];

    printf("Enter a string:");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    char *start = str[0];

    for (int i = 0; i < sizeof(str); i++)
    {
        printf("%c\n",*(start+i));
    }
    


    return 0;
}