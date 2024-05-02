#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

struct database_header_t
{
    unsigned short version;
    unsigned short employees;
    unsigned int filesize;
};

// everything in linux is a file
int main(int argc, char *argv[])
{
    /*
    File Descriptors
    0 - stdin
    1 - stdout -> outputs
    2 - stderr -> errors to be filtered for specific logging
    */

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    char *mydata = "This is some data to write to the file\n";
    int len = write(fd, mydata, strlen(mydata));

    close(fd);

    // file input

    struct stat dbStat = {0};

    struct database_header_t head = {0};

    // int fd2 = open("./my-db.db", O_RDWR | O_CREAT, 0644);

    int fd2 = open("./malicious-db.db", O_RDWR | O_CREAT, 0644);
    if (fd2 == -1)
    {
        perror("Error opening file");
        return -1;
    }

    if (read(fd2, &head, sizeof(head)) != sizeof(head))
    {
        perror("Error reading file");
        return -1;
    }

    printf("Version: %d\n", head.version);
    printf("Employees: %d\n", head.employees);
    printf("Filesize: %d\n", head.filesize);

    if (fstat(fd2, &dbStat) < 0)
    {
        perror("Error getting file stats");
        return -1;
    }

    printf("DB File size reported by stat: %ld\n", dbStat.st_size);

    if (dbStat.st_size != head.filesize)
    {
        printf("GET OUTTA HERE HACKER!\n");
        close(fd2);
        return -2;
    }

    close(fd2);

    return 0;
}