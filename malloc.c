#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));

    printf("Memory at: %p, initial value %d\n",ptr,*ptr);
    *ptr = 42;
    printf("value of allocated int: %d\n",*ptr);
    // Free the allocated memory
    printf("size of pointer is %zu\n", sizeof(ptr));
    printf("Size of an int is %zu\n", sizeof(*ptr));


    free(ptr);
    return 0;
}