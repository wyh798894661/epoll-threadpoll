///
/// @file def.h
/// @brief
/// @author wangyuhang
/// @date 2016-03-21
///
#ifndef __DEF__
#define __DEF__

#include <iostream>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <deque>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <map>

using namespace std;

typedef unsigned long ULONG;

/// @brief 为了服务器接收到client的信息把数据和client的套接字连接到一起
struct G_DataSocket
{
	int nSocket;
	void *pStr;
};

#endif
