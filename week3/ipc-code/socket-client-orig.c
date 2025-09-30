#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SOCK_PATH "unix_socket_example"

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int filed = open(argv[1], O_RDONLY);
    struct stat stat_buffer;
    fstat(filed, &stat_buffer);
    printf("%ld", stat_buffer.st_size);
    int file_size = stat_buffer.st_size;

    int sockfd, portno, n;

    struct sockaddr_un serv_addr;
    char buffer[256];

    /* create socket, get sockfd handle */
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* fill in server address */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_PATH);

    bzero(buffer, 256);
    sprintf(buffer, "%d", file_size);
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /* send user message to server */
    printf("Sending file size %d\n", file_size);

    // read(filed , buffer , file_size) ;
    int bytes_read = 0;
    while (bytes_read  <= file_size ){
        bzero(buffer, 256);
        read(filed, buffer, 256) ;
        printf("%s" , buffer) ;

        n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        bytes_read += 256 ;
    }

    if (n < 0)
        error("ERROR writing to socket");

    close(sockfd);
    return 0;
}
