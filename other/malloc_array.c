#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for an array of 10 shorts
    short *array = (short *)malloc(10 * sizeof(short));
    if (array == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = i * 2; // Example initialization
    }

    // Print the array
    for (int i = 0; i < 10; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }

    // Free the allocated memory
    free(array);

    return 0;
}