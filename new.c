#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int x = 5;
printf("%zu\n", sizeof(x));     // prints the size of an int (usually 4)
printf("%zu\n", sizeof(int));   // also prints size of int

char arr[10];
printf("%zu\n", sizeof(arr));   // prints 10 (size of the array)

printf("%zu\n", sizeof(double)); // usually 8

}