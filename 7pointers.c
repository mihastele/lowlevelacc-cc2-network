#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// int g_numEmployees = 0; // global variables are a big nono

struct employee_t
{
    int id;
    char firstname[64];
    char lastname[64];
    float income;
    bool ismanager;
};

int initialize_employee(struct employee_t *employee)
{
    static int numEmployees = 0;
    numEmployees++;

    employee->id = numEmployees;
    employee->income = 1000;
    employee->ismanager = false;
    strcpy(employee->firstname, "Ralph");
    strcpy(employee->lastname, "Haelle");

    return numEmployees;
}

int main()
{
    int x = 3;

    int *pX = &x;

    printf("x = %d\n", *pX);
    printf("pX = %p\n", pX);

    int n = 4;

    struct employee_t *employees = malloc(sizeof(struct employee_t) * n);

    if (employees == NULL)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        initialize_employee(&employees[i]);
        printf("Employee %d: %s %s\n", employees[i].id, employees[i].firstname, employees[i].lastname);
    }
    // initialize_employee(&employees[0]);

    printf("%s's income is %f\n", employees[0].firstname, employees[0].income);

    free(employees);
    // use after free, we remove the power of using it in the future
    employees = NULL;
}