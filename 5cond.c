#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    int temp;

    printf("Enter the temperature in Celsius: ");
    scanf("%d", &temp);

    if (temp < 0)
    {
        printf("It's freezing!\n");
    }
    else if (temp < 10)
    {
        printf("It's cold!\n");
    }
    else if (temp < 20)
    {
        printf("It's chilly!\n");
    }
    else if (temp < 30)
    {
        printf("It's warm!\n");
    }
    else
    {
        printf("It's hot!\n");
    }
}