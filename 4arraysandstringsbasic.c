#include <stdio.h>
#include <string.h>

#define MAX_PERSONS 1024
#define MAX_IDS 32

#define DEBUG

int main()
{
    // int ids[MAX_IDS];
    // int ids[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ids[MAX_IDS] = {0x00, 0x10, 0x20, 0x30, 0x40};

    for (int i = 0; i < MAX_IDS; i++)
    {
        printf("ids[%d] = %d\n", i, ids[i]);
    }

    char mystr1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char mystr2[] = {'H', 'e', 'l', 'l', 'o', 0}; // strings must be null terminated
    char mystr[] = "Hello World";
    char *myotherstr = "Hello Worlddd";

    strcpy(mystr, "Heii");
    strncpy(mystr, "Coookiies", 5);

    printf("mystr = %s\n", mystr);

    return 0;
}