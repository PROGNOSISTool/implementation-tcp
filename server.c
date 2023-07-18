#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 128
#define PORT 44344
#define SA struct sockaddr

void func(int connfd) {
    char input[MAX];
    int n;

    while (1) {
        bzero(input, MAX);

        read(connfd, input, sizeof(input));
        char* pch = strstr(input, "\n");
        if (pch != NULL) {
            strncpy(pch, "\0", 1);
        }

        size_t len = strlen(input);
        char* output = (char*)malloc((len + 1) * sizeof(char));
        output[len] = '\0';

        for (int i = 0; i < len; i++) {
            output[i] = input[len - 1 - i];
        }

        // and send that buffer to client
        write(connfd, output, sizeof(output));

        if (strncmp("STOP", input, 4) == 0) {
            printf("Stopping...\n");
            break;
        }
    }
}

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int i = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void*)&i, sizeof(i));
    setsockopt(sockfd, IPPROTO_TCP, TCP_QUICKACK, (void*)&i, sizeof(i));

    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    } else
        printf("server accept the client...\n");

    func(connfd);

    close(sockfd);
}
