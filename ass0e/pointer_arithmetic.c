#include <stdio.h>

int main() {
    // Your code here


    int arr[5] =  {10, 20, 30, 40, 50};

    int *ptr = &arr[0];


    for (int i= 0; i < 5; i++)
    {
        printf("%i,",*(ptr+i));
    }
    
    return 0;
}