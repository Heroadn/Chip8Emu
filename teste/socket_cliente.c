#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define MAX_DATA_SIZE 128

int main(void)
{
    char buff[MAX_DATA_SIZE];
    int len;

    struct sockaddr_storage client_addr;
    socklen_t addr_size;

    struct addrinfo hints, *servinfo;
    int sockfd, status = 0;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "erro em getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }

    sockfd = socket(servinfo->ai_family,
                    servinfo->ai_socktype,
                    servinfo->ai_protocol);

    connect(sockfd,
            servinfo->ai_addr,
            servinfo->ai_addrlen);

    while (strcmp(buff, "LOGOUT") != 0)
    {
        //read
        recv(sockfd,
             buff,
             MAX_DATA_SIZE,
             0);
        printf("Servidor: %s\n", buff);

        //cleaning buffer and reading input
        memset(buff,
               0,
               sizeof(buff));
        fgets(buff,
              MAX_DATA_SIZE,
              stdin);
        
        //sending message to server
        len = strlen(buff);
        send(sockfd,
             buff,
             len,
             0);
    }

    freeaddrinfo(servinfo);
    close(sockfd);
    return 0;
}