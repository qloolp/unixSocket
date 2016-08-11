

//echo server

#include "unp.h"

void echo(int sockfd)
{
    ssize_t n;
    char buff[MAXLINE];
again:
    while((n=read(sockfd,buff,MAXLINE))>0)
    {
        write(sockfd,buff,n);   //原样写回
    }

    if(n<0)
    {
        fprintf(stderr, "数据读取出错\n");
        fflush(stdout);
    }
    goto again;
    //等于0则为EOF正常结束。
}




int main(int argc, char** argv) //文件名，port
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    if(argc != 2)
    {
        fprintf(stderr, "usage:<server.out> <port>\n");
        exit(1);
    }

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr,"不能创建套接字\n");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if((bind(listenfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in)))==-1)
    {
        fprintf(stderr, "无法捆绑端口\n");
        exit(1);
    }

    if((listen(listenfd, 10))==-1)
    {
        fprintf(stderr,"无法监听端口\n");
        exit(1);
    }

    while(1)
    {
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd,(struct sockaddr*)&cliaddr, &clilen))==-1)
        {
            fprintf(stderr, "accept出错\n");
            exit(1);
        }

        if((childpid = fork()) == 0)  //子进程
        {
            close(listenfd);
            echo(connfd);
            exit(0);
        }

        close(connfd);      //父进程
    }
    return 0;
}
