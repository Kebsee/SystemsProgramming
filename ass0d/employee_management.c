#include <stdio.h>
#include <stdlib.h>
#define MAX_EMPLOYEES 10

typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

int main(int argc, char *argv[]) {
    // Entry point of the program
    printf("Employee Management System\n");

    Employee employees[MAX_EMPLOYEES];

    int cont = 0;

    char yn = 'y';

    while (yn == 'y') {
        printf("Enter employee details:\n");
        printf("Name:");
        scanf("%s", employees[cont].name);

        printf("Age:");
        scanf("%d", &employees[cont].age);

        // Consume the newline left by the previous scanf
        getchar();

        printf("Salary:");
        scanf("%f", &employees[cont].salary);

        // Consume the newline left by scanf("%f")
        getchar();

        if (employees[cont].salary > 50000) {
            printf("Employee %s is highly paid.\n", employees[cont].name);
        }else{
            printf("Employee %s is not highly paid.\n", employees[cont].name);
        }

        printf("Do you want to enter another employee? (y/n):");
        scanf("%c", &yn);
    }

    return 0;
}
