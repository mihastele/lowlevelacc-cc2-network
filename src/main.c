#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage()
{
    printf("Usage: ./db -f <filepath> [-n] <<to create a new DB>> \n");
}

void list_employees(struct dbheader_t *header, struct employee_t *employees)
{
    printf("Employees:\n");
    for (int i = 0; i < header->count; i++)
    {
        printf("Employee %d:\n", i);
        printf("\tName: %s\n", employees[i].name);
        printf("\tAddress: %s\n", employees[i].address);
        printf("\tHours: %d\n", employees[i].hours);
    }
}

int main(int argc, char *argv[])
{

    char *filepath = NULL;
    char *addString = NULL;
    bool newfile = false;
    bool list = false;
    int c;

    int dbfd = -1; // database file descriptor
    struct dbheader_t *header = NULL;
    struct employee_t *employees = NULL;

    while ((c = getopt(argc, argv, "nlf:a:")) != -1) // options are n, l, f(: means it has data), a(: means it has data)
    {
        switch (c)
        {
        case 'n':
            newfile = true;
            break;

        case 'f':
            filepath = optarg;
            break;
        case 'a':
            addString = optarg;
            break;
        case 'l':
            list = true;
            break;
        case '?':
            printf("Unknown option: %c\n", c);
            break;
        default:
            return -1;
        }
    }

    if (filepath == NULL)
    {
        printf("No filepath specified\n");
        print_usage();
        return -1;
    }

    if (newfile)
    {
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("Unable to create DB file\n");
            return -1;
        }
        if (create_db_header(dbfd, &header) == STATUS_ERROR)
        {
            printf("Unable to create DB header\n");
            return -1;
        }
    }
    else
    {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("Unable to open DB file\n");
            return -1;
        }
        if (validate_db_header(dbfd, &header) == STATUS_ERROR)
        {
            printf("Unable to validate DB header\n");
            return -1;
        }
    }

    if (read_employees(dbfd, header, &employees) != STATUS_SUCCESS)
    {
        printf("Unable to read employees\n");
        return -1;
    }

    if (addString)
    {
        realloc(employees, sizeof(struct employee_t) * (++header->count));
        add_employee(header, employees, addString);
    }

    // printf("New file: %d\n", newfile);
    // printf("filepath: %s\n", filepath);

    if (list)
    {
        list_employees(header, employees);
    }

    output_file(dbfd, header, employees);

    return 0;
}