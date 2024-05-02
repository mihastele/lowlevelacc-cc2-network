#include <stdio.h>
#include <stdbool.h>

#define MAX_IDS 32
#define MAX_EMPLOYEES 100

struct employee_t
{
    int id;
    char firstname[64];
    char lastname[64];
    float income;
    bool ismanager;
};

// union makes enough space only for the largest member, in ths case int x
union myunion_u
{
    int x;
    char c;
    short s;
};

// special struct modifiers
// this modifier makes sure that optimizations in different compilers don't change the size of the struct (padding, reordering, etc.)
// which breaks compatibility
__attribute__((packed)) struct mystruct_t
{
    char c[64];
    int x;
    int y;
    short s;
};

int main()
{
    struct employee_t employees[MAX_EMPLOYEES];

    int i = 0;
    for (i = 0; i < MAX_EMPLOYEES; i++)
    {
        employees[i].id = i;
        employees[i].income = 0;
        employees[i].ismanager = false;
    }

    union myunion_u u;
    u.x = 0x41424344;

    printf("%hx %hhx\n", u.s, u.c);

    struct mystruct_t s;
    printf("sizeof(s) = %ld\n", sizeof(s));
}