#include <sys/types.h>
#include <sys/socket.h>
//#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>

#define PORT 5200
#define HOST 0
#define QUEUE 20
int conn;

void thread_task()
{
	printf("other thread\n");
}

int main()
{
    printf("AF_INET %d \r\n", AF_INET);
    printf("SOCK_STREAM %d \r\n", SOCK_STREAM);
    int ss = socket(AF_INET, SOCK_STREAM, 0); // 创建成功则返回一个socketfd
    printf("socketFd %d\n", ss);
    printf("master Only\n");
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    printf("INADDR_ANY %d\n", INADDR_ANY);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ss, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind failure");
        exit(1);
    }
    if (listen(ss, QUEUE) == -1)
    {
        perror("listen failure");
        exit(1);
    }

    struct sockaddr_in client_sockaddr;
    socklen_t length = sizeof(client_sockaddr);
    conn = accept(ss, (struct sockaddr *)&client_sockaddr, &length);
    if (conn < 0)
    {
        perror("conn failure");
        exit(1);
    }

    char buffer[1024];
    // 创建另一个线程
    std::thread t(thread_task);
    t.join();
    char buf[1024];
    // 主线程
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        if (fgets(buf, sizeof(buf), stdin) != NULL)
        {
            send(conn, buf, sizeof(buf), 0);
        }

        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0)
        {
            break;
        }
        printf("buffer %s\n", buffer);
        send(conn, buffer, len, 0);
    }
    close(conn);
    close(ss);
    return 0;
}
