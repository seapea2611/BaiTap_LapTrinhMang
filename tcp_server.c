#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4) {
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
    
     FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("Error allocating memory");
        return 1;
    }
    fread(buffer, 1, size, file);
    
     if (send(client, buffer,size, 0) == -1)
        {
            perror("send() failed");
            exit(EXIT_FAILURE);
        }
    fclose(file);
    free(buffer);
    // mở file
    FILE *fp = fopen(argv[3], "a");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buff[1024];
    int ret;
    while (1) {
        ret = recv(client, buff, sizeof(buff), 0);
        if (ret <= 0) {
            break;
        }
        fprintf(fp, "%s", buff);
    }

    fclose(fp);
    close(client);
    close(listener);
    return 0;
}