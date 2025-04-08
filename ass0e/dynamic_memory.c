#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int ints = 0;
    scanf("%d",&ints);
    printf("Enter %i integers:",ints);

    int *array = (int *)malloc(ints * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < ints; i++)
    {
        scanf("%d",&array[i]);
    }

    for (int i = 0; i < ints; i++)
    {
        printf("%i",array[i]);
    }
    

    free(array);
    
    return 0;
}