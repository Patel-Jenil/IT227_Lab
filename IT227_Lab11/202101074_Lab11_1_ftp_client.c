#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#define MAXLINE 8192

int open_clientfd(char *hostname, char *port) {

    int clientfd;
    struct addrinfo hints, *listp, *p;
    char host[MAXLINE], service[MAXLINE];
    int flags;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    getaddrinfo(hostname, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next) {

        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;

        flags = NI_NUMERICHOST | NI_NUMERICSERV;
        getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
        printf("Host:%s, Service:%s\n", host, service);

        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
            printf("Connected to server %s at port %s\n", host, service);
            break;
        }

        close(clientfd);
    }

    freeaddrinfo(listp);

    if (!p)
        return -1;
    else
        return clientfd;
}

int main(int argc, char **argv) {
    int clientfd;
    char *host, *port, buf[MAXLINE];
    char file[100];
    host = argv[1];
    port = argv[2];
    clientfd = open_clientfd(host, port);

    printf("Enter file name : ");
    scanf("%s", file);

    if (strcmp(file, "quit") == 0) {
        close(clientfd);
        exit(0);
    }

    write(clientfd, file, strlen(file));
    int o = open("test.txt", O_WRONLY);

    while (1) {
        int bytes = read(clientfd, buf, MAXLINE);

        if (bytes == 0) {
            close(o);
            break;
        }

        if (bytes == 1 && buf[0] == '0') {
            printf("The file could not be opened\n");
            close(clientfd);
            exit(0);
        }

        write(o, buf, bytes);
        fputs(buf, stdout);

        if (buf[0] == '\n')
            break;
    }

    close(clientfd);
    exit(0);
}