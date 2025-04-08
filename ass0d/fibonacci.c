#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n =0;
    printf("Enter a number:");
    scanf("%d",&n);

    int first = 1;
    int result = 0; 
    int second = 1;

    printf("0\n");
    for (int i = 0; i < n-1; i++) {
        if (i == 0) {
            result = first;
        } else if (i == 1) {
            result = second;
        } else {
            result = first + second;
            first = second;
            second = result;
        }
        printf("%d\n", result);
    }
    
    return 0;
}