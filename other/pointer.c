#include <stdio.h>

int main() {
    int num = 42;       // Declare an integer variable
    int *ptr = &num;    // Declare a pointer and store the address of num

    // Print the value of num using the pointer
    printf("Value of num: %d\n", *ptr);

    // Print the address of num
    printf("Address of num: %p\n", (void*)&num);

    // Print the address stored in the pointer
    printf("Address stored in ptr: %p\n", (void*)ptr);

    // Modify the value of num using the pointer
    *ptr = 100;
    printf("New value of num: %d\n", num);

    return 0;
}