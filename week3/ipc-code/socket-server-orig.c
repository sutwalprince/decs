#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "unix_socket_example"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     unlink(SOCK_PATH);

     int sockfd;
     char buffer[256];
     struct sockaddr_un serv_addr, cli_addr;
     int n;

     /* create socket */

     sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     /* fill in socket addres */
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, SOCK_PATH);

     /* bind socket to this address */
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     /* read message from client */

     bzero(buffer,256);
     int len = sizeof(cli_addr);

     printf("Server ready %d\n" , len);
     
     n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&cli_addr, &len);
	//printf("%d" , n ) ;
     int file_size = atoi(buffer) ;
     printf("%d",file_size);

     int rcvd_size = 0 ;
	 while(rcvd_size < file_size){
          bzero(buffer,256);
          n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&cli_addr, &len);
          printf("%s" , buffer) ;
          rcvd_size += 256 ;
    }
     unlink(SOCK_PATH);
     return 0; 
}
