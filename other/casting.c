#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main() {
    // Your code here
    float max_float = FLT_MAX;
    int casted_int = (int)max_float;
    printf("max float %e\n",max_float);
    printf("max int %i\n",casted_int);


    return 0;


}