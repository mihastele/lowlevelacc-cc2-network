#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Oh no! Error opening file");
        return -1;
    }
}