#include<stdio.h>

int main() {
    char name[10];
    int age = 0;


    printf("Enter your name: ");

    scanf("%s", name);

    printf("Enter your age: ");

    scanf("%d", &age);

    printf("Hello, %s! You are %i years old.\n",name,age);


    if (age>=18)
    {
        printf("The user is an adult.\n");
    }else{
        printf("The user is not an adult.\n");
    }
    
    return 0;
}