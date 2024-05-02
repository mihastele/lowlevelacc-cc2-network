#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    // endianess
    // int x = 0x12345678;
    // big endian: 0x12 0x34 0x56 0x78
    // little endian: 0x78 0x56 0x34 0x12
    // network endian: big endian

    // file descriptor, socker is just a file, so it has a file descriptor
    // eligible in server and client
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    printf("Socket created\n");
    printf("Socket fd: %d\n", fd);
    return 0;

    return 0;
}