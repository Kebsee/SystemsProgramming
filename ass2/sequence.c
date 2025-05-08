#include <stdio.h>

int main() {
    char buffer[256];

    printf("Enter a line of text: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}