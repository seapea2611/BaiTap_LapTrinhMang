#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Sai tham so\n");
        return 1;
    }
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;        
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    printf("Khoi tao thanh cong!!!\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client = accept(listener, 
        (struct sockaddr *)&client_addr, 
        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n", 
        client,
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));

    FILE *fp = fopen(argv[2], "a");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    char buff[5000];
    int ret;
    ret = recv(client, buff, sizeof(buff), 0);
        if (ret <= 0) {
            perror("listen() failed");
            return 1;
        }
    fprintf(fp, "%s %s %s", inet_ntoa(client_addr.sin_addr), asctime(local_time), buff);

    fclose(fp);
    close(client);
    close(listener);
    return 0;
}