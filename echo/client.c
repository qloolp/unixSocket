
//echo client

#include "unp.h"

void echo(FILE* fp, int sockfd)
{
    char sendline[MAXLINE],recvline[MAXLINE];  //全为'\0'
    while(fgets(sendline,MAXLINE,fp) != NULL)
    {
        write(sockfd,sendline,strlen(sendline)+1);           //需要将'\0'也发送过去
        if((read(sockfd,recvline,MAXLINE)) == 0)
        {
            fprintf(stderr,"server terminated prematurely\n");
        }
        fputs(recvline,stdout);
        fflush(stdout);
    }
}

int main(int argc, char** argv) //文件名，IP地址，port
{
    int sockfd;
    struct sockaddr_in servadder;

    if(argc != 3)
    {
        fprintf(stderr,"usage:<client.out> <IPaddress> <port>\n");
        exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr,"不能创建套接字\n");
        exit(1);
    }

    memset(&servadder,0,sizeof(struct sockaddr_in));
    servadder.sin_family = AF_INET;
    servadder.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &servadder.sin_addr);

    if((connect(sockfd, (struct sockaddr*)&servadder, sizeof(struct sockaddr_in)))==-1)
    {
        fprintf(stderr,"连接不成功\n");
        exit(1);
    }

    echo(stdin, sockfd);
    exit(0);
}
