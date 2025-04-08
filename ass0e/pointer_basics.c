#include <stdio.h>

int main() {
    // Your code here
    int num = 42; // Declare an integer variable and assign it a value
    int *ptr = &num; // Declare a pointer to an integer and assign it the address of the variable

    printf("Value of the variable: %d\n", num); // Print the value of the variable directly
    printf("Address of the variable: %p\n", ptr); // Print the address of the variable using the pointer
    printf("Value of the variable using the pointer: %d\n", *ptr); // Print the value of the variable using the pointer (dereferencing)


    return 0;
}