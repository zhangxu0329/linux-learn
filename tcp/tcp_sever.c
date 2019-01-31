#include <func.h>

int main(int argc,char *argv[])
{
    args_check(argc,3);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(struct sockaddr_in));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);//struct in_addr 的成员只有一个就是s_addr是旧的接口
    int ret;
    ret=bind(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr_in));
    if(ret==-1)
    {
        perror("bind");
        return -1;
    }
    listen(socketfd,10);
    int new_fd;
    struct sockaddr_in client;
    socklen_t addrlen;
    memset(&client,0,sizeof(client));
    new_fd=accept(socketfd,(struct sockaddr*)&client,&addrlen);
    if(new_fd==-1)
    {
        perror("accept");
        return -1;
    }
    char buf[128]={0};
    send(new_fd,"hello",5,0);
    ret=recv(new_fd,buf,sizeof(buf),0);
    if(-1==ret)
    {
        perror("recv");
        return -1;
    }
    printf("this is server,i recv %s\n",buf);
    close(new_fd);
    close(socketfd);
};
