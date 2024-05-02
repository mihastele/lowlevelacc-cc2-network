#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

int parse_file_header(int fd, int *numEmployeesOut)
{
    if (fd == -1)
    {
        printf("Invalid file descriptor\n");
        return STATUS_ERROR;
    }

    struct dbheader_t header = {0};

    if (read(fd, &header, sizeof(header)) != sizeof(header))
    {
        printf("Error reading file header\n");
        return STATUS_ERROR;
    }

    *numEmployeesOut = header.count;
    return STATUS_SUCCESS;

    return 0;
}

int create_db_header(int fd, struct dbheader_t **headerOut)
{
    // struct dbheader_t header = {0}; // set all fields to 0
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));

    if (header == -1)
    {
        printf("Error allocating memory for header\n");
        return STATUS_ERROR;
    }

    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;
}

int validate_db_header(int fd, struct dbheader_t **headerOut)
{
    if (fd == -1)
    {
        printf("Invalid file descriptor\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == -1)
    {
        printf("Error allocating memory for header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t))
    {
        printf("Error reading file header\n");
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->filesize = ntohl(header->filesize);

    if (header->magic != HEADER_MAGIC)
    {
        printf("Invalid header magic\n");
        free(header);
        return STATUS_ERROR;
    }

    if (header->version != 1)
    {
        printf("Invalid version\n");
        free(header);
        return STATUS_ERROR;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size)
    {
        printf("Corrupted DB\n");
        free(header);
        return STATUS_ERROR;
    }

    *headerOut = header;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut)
{
    int count = dbhdr->count;
    struct employee_t *employees = calloc(count, sizeof(struct employee_t));

    if (employees == -1)
    {
        printf("Error allocating memory for employees\n");
        return STATUS_ERROR;
    }

    read(fd, employees, count * sizeof(struct employee_t));

    int i = 0;
    for (i = 0; i < count; i++)
    {
        employees[i].hours = ntohl(employees[i].hours);
    }

    *employeesOut = employees;

    return STATUS_SUCCESS;
}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring)
{

    char *name = strtok(addstring, ",");
    char *addr = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");

    // printf("name: %s ", name);
    // printf("addr: %s ", addr);
    // printf("hours: %s\n", hours);

    strncpy(employees[dbhdr->count - 1].name, name, sizeof(employees[dbhdr->count - 1].name));
    strncpy(employees[dbhdr->count - 1].address, addr, sizeof(employees[dbhdr->count - 1].address));
    employees[dbhdr->count - 1].hours = atoi(hours);

    return STATUS_SUCCESS;
}

void output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees)
{
    if (fd == -1)
    {
        printf("Invalid file descriptor\n");
        // return STATUS_ERROR;
        return;
    }

    int realcount = dbhdr->count;

    dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (realcount * sizeof(struct employee_t)));
    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->version = htons(dbhdr->version);
    dbhdr->count = htons(dbhdr->count);

    lseek(fd, 0, SEEK_SET);

    write(fd, dbhdr, sizeof(struct dbheader_t));

    for (int i = 0; i < realcount; i++)
    {
        employees[i].hours = htonl(employees[i].hours);
        write(fd, &employees[i], sizeof(struct employee_t));
    }

    return;
}