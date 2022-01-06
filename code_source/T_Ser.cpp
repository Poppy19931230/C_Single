#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>

#define PORT    5200
#define QUEUE   20   
int conn;

void thread_task()
{

}

int main()
{
    printf("AF_INET %d \r\n", AF_INET);
    printf("%d \r\n", SOCK_STREAM);
    int ss = socket(AF_INET, SOCK_STREAM, 0);// 创建成功则返回一个socketfd
    printf("%d\n", ss);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    printf();
}