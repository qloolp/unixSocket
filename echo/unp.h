#ifndef UNP_H_INCLUDED
#define UNP_H_INCLUDED

#define MAXLINE 4096




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




#include <netinet/in.h>
/*
struct in_addr;  ipv4地址

struct sockaddr_in;   ipv4套接字地址结构
--------------------------------------------
struct in6_addr

struct sockarrd_in6;

struct sockaddr_storage; 新通用套接字地址结构


uint16_t htons(uint16_t)
uint32_t htonl(uint32_t) 返回网络字节序的值
uint16_t ntohs(uint16_t)
uint32_t ntohl(uint32_t) 返回主机字节序的值

*/

#include <sys/socket.h>
/*
struct sockaddr;  通用套接字地址结构

*/


#include <string.h>
/*
void *memset(void* dest, int c, size_t len);
void *memcpy(void* des, const void* src, size_t nbytes);
int memcmp(const void* ptr1, const void* ptr2, size_t nbytes);
*/

#include <arpa/inet.h>
/*
仅ipv4
int inet_aton(const char* strptr, struct in_addr* addrptr);;
char* inet_ntoa(struct in_addr inaddr);

通用
inet_pton
inet_ntop
*/















#endif // UNP_H_INCLUDED
