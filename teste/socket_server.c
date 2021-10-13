#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <gtk/gtk.h>

#define PORT "3490"
#define BACKLOG 5
#define BUFF_SIZE 128
//compile it using `pkg-config --cflags gtk+-3.0`

int socket_create(const char *port)
{
    struct addrinfo hints, *servinfo;
    int sockfd, status = 0;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "erro em getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }

    sockfd = socket(servinfo->ai_family,
                    servinfo->ai_socktype,
                    servinfo->ai_protocol);
    //fcntl(sockfd, F_SETFL, O_NONBLOCK);

    bind(sockfd,
         servinfo->ai_addr,
         servinfo->ai_addrlen);
    freeaddrinfo(servinfo);

    return sockfd;
}

int main(void)
{
    GtkWidget *janela;
    char buff[BUFF_SIZE] = "Digite a mensagem[128]\n";
    int len = strlen(buff);

    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    int sockfd, clientfd, status = 0;

    sockfd = socket_create(PORT);

    listen(sockfd,
           BACKLOG);

    addr_size = sizeof(client_addr);
    clientfd = accept(sockfd,
                      (struct sockaddr *)&client_addr,
                      &addr_size);

    len = strlen(buff);
    send(clientfd,
         buff,
         BUFF_SIZE,
         0);

    close(sockfd);
    return 0;
}