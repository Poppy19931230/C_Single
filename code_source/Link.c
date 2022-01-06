#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define PATH "/var/lib/docker/overlay2"
static char Path_c[60] = {0};

int _Init()
{
    struct sockaddr_un address;
    struct sockaddr_un local;
    struct timeval tv_out;
    static int sockFd = -1;
    tv_out.tv_sec = 0;
    tv_out.tv_usec = 50;
    readlink(&Path_c, );
    sockFd = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (sockFd < 0)
    {
        fprintf(stderr, "sockFd = %d \n", sockFd);
        return;
    }
    setsockopt(sockFd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));
    bzero(&local, sizeof(local));
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, PATH);
    local.sun_family = AF_UNIX;
//  strncpy(local.sun_path, Path_c, sizeof(Path_c)-1);
}
int main()
{
    while(1)
    {
        _Init();
    }
    return 0;
}