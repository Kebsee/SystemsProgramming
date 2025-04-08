#include <stdio.h>

struct Student {
    char name[50];
    int age;
    float gpa;
};

int main() {
    struct Student student;

    // Taking input from the user
    printf("Enter Student Name: ");
    scanf("%49s", student.name); // Limiting input to avoid buffer overflow

    printf("Enter Student Age: ");
    scanf("%d", &student.age);

    printf("Enter Student GPA: ");
    scanf("%f", &student.gpa);

    // Printing the student's details
    printf("Name: %s, Age: %d, GPA: %.2f\n", student.name, student.age, student.gpa);

    return 0;
}