#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // endianess
    // int x = 0x12345678;
    // big endian: 0x12 0x34 0x56 0x78
    // little endian: 0x78 0x56 0x34 0x12
    // network endian: big endian

    // file descriptor, socker is just a file, so it has a file descriptor
    // eligible in server and client
    // int fd;
    // fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (fd < 0)
    // {
    //     perror("socket");
    //     return -1;
    // }
    // printf("Socket created\n");
    // printf("Socket fd: %d\n", fd);
    // return 0;

    // CLIENT

    if (argc != 2)
    {
        printf("Usage: %s <server IP>\n", argv[0]);
        return -1;
    }

    struct sockaddr_in serverInfo = {0};
    serverInfo.sin_family = AF_INET;                 // IPv4
    serverInfo.sin_addr.s_addr = inet_addr(argv[1]); // IP address
    serverInfo.sin_port = htons(8784);               // port number htons -> host to network short (converts host byte order to network byte order - endianess)

    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    printf("Socket created\n");
    printf("Socket fd: %d\n", fd);

    if (connect(fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) < 0)
    {
        perror("connect");
        close(fd);
        return -1;
    }

    return 0;
}