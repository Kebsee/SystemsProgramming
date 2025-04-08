#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int arr[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d",&arr[i][j]);
        }
        
    }

    int *ptr = &arr[0][0];
    for (int i = 0; i < 3 * 3; i++) {
        printf("%d ", *(ptr + i));
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }

    return 0;
}