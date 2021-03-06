

#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

#include "Socket.h"
#include <string>


class SocketUtil
{
public:
    static bool bind(SOCKET sockfd, std::string ip, uint16_t port);
    static void setNonBlock(SOCKET fd);
    static void setBlock(SOCKET fd, int writeTimeout=0);
    static void setReuseAddr(SOCKET fd);
    static void setReusePort(SOCKET sockfd);
    static void setNoDelay(SOCKET sockfd);
    static void setKeepAlive(SOCKET sockfd);
    static void setNoSigpipe(SOCKET sockfd);
    static void setSendBufSize(SOCKET sockfd, int size);
    static void setRecvBufSize(SOCKET sockfd, int size);
    static std::string getPeerIp(SOCKET sockfd);
    static uint16_t getPeerPort(SOCKET sockfd);
    static int getPeerAddr(SOCKET sockfd, struct sockaddr_in *addr);
    static void close(SOCKET sockfd);
    static bool connect(SOCKET sockfd, std::string ip, uint16_t port, int timeout=0);
    static uint16_t get_local_port(int fd);
};


#endif // _SOCKET_UTIL_H




