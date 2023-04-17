#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LENGTH 1000
int main(int argc, char *argv[]) {
      if (argc != 3)
    {
        printf("Sai tham so.\n");
        return 1;
    }
     int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }
    char input[MAX_LENGTH];
    printf("Nhap vao mot xau: ");
    fgets(input, MAX_LENGTH, stdin);
    if(send(client, input, strlen(input),0) == -1) {
        perror("send failed");
        return 1;
    }

    close(client);
}