#include <stdio.h>

// Function to demonstrate pass by value
void passByValue(int x) {
    x = 20; // This change will not affect the original variable
    printf("Inside passByValue: x = %d\n", x);
}

// Function to demonstrate pass by pointer
void passByPointer(int *x) {
    *x = 20; // This change will affect the original variable
    printf("Inside passByPointer: *x = %d\n", *x);
}

int main() {
    int a = 10;
    int b = 10;

    printf("Before passByValue: a = %d\n", a);
    passByValue(a);
    printf("After passByValue: a = %d\n", a);

    printf("\nBefore passByPointer: b = %d\n", b);
    passByPointer(&b);
    printf("After passByPointer: b = %d\n", b);

    return 0;
}