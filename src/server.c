#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

// Design protocol, and version it for backwards compatibility

typedef enum
{
    PROTO_HELLO,
} proto_type_e;

// TLV - Type, Length, Value
typedef struct
{
    proto_type_e type;
    unsigned short len;
} proto_hdr_t;

void handle_Client(int fd)
{
    char buf[4096] = {0};
    proto_hdr_t *hdr = buf;
    hdr->type = htonl(PROTO_HELLO);
    hdr->len = sizeof(int);
    int reallen = hdr->len;
    hdr->len = htons(hdr->len);

    int *data = (int *)&hdr[1];
    *data = htonl(1);

    write(fd, hdr, sizeof(proto_hdr_t) + reallen);
}

int main()
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

    // SERVER
    struct sockaddr_in serverInfo = {0};
    struct sockaddr_in clientInfo = {0};
    int clientSize = 0;
    serverInfo.sin_family = AF_INET;   // IPv4
    serverInfo.sin_addr.s_addr = 0;    // every IP address
    serverInfo.sin_port = htons(8784); // port number htons -> host to network short (converts host byte order to network byte order - endianess)

    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    printf("Socket created\n");
    printf("Socket fd: %d\n", fd);

    // bind
    if (bind(fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) < 0)
    {
        perror("bind");
        close(fd);
        return -1;
    }

    // listen
    if (listen(fd, 0) < 0)
    {
        perror("listen");
        close(fd);
        return -1;
    }

    // accept

    while (1)
    {
        int clientFd;
        clientFd = accept(fd, (struct sockaddr *)&clientInfo, &clientSize);
        if (clientFd < 0)
        {
            perror("accept");
            close(fd);
            return -1;
        }

        handle_Client(clientFd);

        close(clientFd);
    }

    return 0;
}