#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 1024
int main(int argc, char *argv[]) {
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
    
    char mssv[MAX], hoten[MAX], ngaysinh[MAX], diemtb[MAX];

    printf("Nhap vao mssv: ");
    fgets(mssv, MAX, stdin);
    mssv[strcspn(mssv, "\n")] = 0; 

    printf("Nhap vao ho ten: ");
    fgets(hoten, MAX, stdin);
    hoten[strcspn(hoten, "\n")] = 0;

    printf("Nhap vao ngaysinh: ");
    fgets(ngaysinh, MAX, stdin);
    ngaysinh[strcspn(ngaysinh, "\n")] = 0;

    printf("Nhap vao diem tb: ");
    fgets(diemtb, MAX, stdin);
    diemtb[strcspn(diemtb, "\n")] = 0;

    char buff[4 * MAX + 4];
    sprintf(buffer, "%s %s %s %s", mssv, hoten, ngaysinh, diemtb);
    
    if(send(client, buff, strlen(buff),0) == -1) {
        perror("send failed");
        return 1;
    }
    printf("success");
    close(client);
}