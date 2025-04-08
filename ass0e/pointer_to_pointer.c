#include <stdio.h>
#include <stdlib.h>

int main() {

    int num;

    scanf("%d",&num);

    int *ptr1 = &num;
    int *ptr2 = ptr1;


    printf("Value of num: %i\n",num);
    printf("Value using ptr1: %i\n",*ptr1);
    printf("Value using ptr2: %i\n",*ptr2);

    return 0;
}