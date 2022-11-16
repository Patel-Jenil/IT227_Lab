#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <fcntl.h>
#define MAXLINE 8192
#define LISTENQ 1024

int open_listenfd(char *port) {
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;
    char host[MAXLINE], service[MAXLINE];
    int flags;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    getaddrinfo(NULL, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next) {

        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

        flags = NI_NUMERICHOST | NI_NUMERICSERV;
        getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
        printf("Host:%s, Service:%s\n", host, service);

        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;

        close(listenfd);
    }

    freeaddrinfo(listp);
    if (!p)
        return -1;

    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
        return -1;
    }

    return listenfd;
}
void *thread_fn_one_param(void *arg) {
    int *p = arg;
    int connfd = *p;
    size_t n;
    char buf[MAXLINE];
    n = read(connfd, buf, MAXLINE);
    int fd = open(buf, O_RDONLY);
    if (fd < 0) {
        buf[0] = '0';
        write(connfd, buf, 1);
        void *tp;
        close(connfd);
        return tp;
    }

    while ((n = read(fd, buf, MAXLINE)) != 0) {
        write(connfd, buf, n);
    }

    close(connfd);
}

int main(int argc, char **argv)
{
    int listenfd, connfd[LISTENQ];
    pthread_t threadID[LISTENQ];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    listenfd = open_listenfd(argv[1]);
    int cnt = 0;

    while (1) {
        printf("Waiting to connect with a new client\n");
        clientlen = sizeof(struct sockaddr_storage);
        connfd[cnt] = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

        getnameinfo((struct sockaddr *)&clientaddr, clientlen,
                    client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        printf("Communication Started\n");
        int err = pthread_create(&threadID[cnt], NULL, thread_fn_one_param, (void *)&connfd[cnt]);
        if (err != 0)
            printf("Error! Thread cannot be created: %s\n", strerror(err));
    }
    exit(0);
}