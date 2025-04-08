#include <stdio.h> // for printf
#include <math.h> // for pow function 
#define PI 3.14159

int main(int argc, char *argv[]) {
    // Part 1 (stdio is required for printf)
    printf("Hello,World!\nWelcome to C\n");

    // Part 2 
    int age = 25;
    float height = 1.75;
    double weight = 68.5;
    char grade = 'A';

    // Part 3
    printf("Age: %i, Height: %.2f m, Weight: %.1lf kg, Grade: %c\n",age,height,weight,grade);


    // // Part 4 
    // // Use #define for simple, untyped constants 
    // that need to be replaced by the preprocessor
    //  before compilation. Use const when you want
    //   type safety, scope control, and better
    //    debugging support during compilation.
    printf("%.3f\n",PI);


    // part 5 
    printf("int: %zu, float: %zu, double: %zu, char:%zu\n",sizeof(int),sizeof(float),sizeof(double),sizeof(char));


    // part 6

    int a = 5;
    int b = 3;
    float c = 2.5;


    printf("%i,",a+b);
    printf("%i,",a-b);

    printf("%i,",a*b);
    printf("%i,",a/b); //1 as it discards the values after .
    printf("%i,",a%b);
    printf("%f,",a+c); // crazy number if %i normal if %f
    printf("a^b = %.2f\n", pow(a, b)); // have to include the -lm flag 

    // part 7 

    float decimal  = 3.7;
    int truncated = (int)decimal ;

    printf("%f,",floor(decimal));
    printf("%f,",ceil(decimal));
    printf("%f,",round(decimal));

    // C uses explicit casting (e.g., (float)) or implicit casting depending 
    // on the operation, and type safety is stricter.
    
    // Python uses built-in conversion functions (e.g., int(), float())
    //  and is more flexible with dynamic typing
    return 0;
    
}