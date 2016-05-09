///
/// @file SendMessThread.h
/// @brief 发送消息线程 server->client
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __G_SENDMESSTHREAD__
#define __G_SENDMESSTHREAD__

#include "def.h"
#include "Thread.h"
#include "ThreadPool.h"
#include "Queue.h"
#include "Data.h"

class G_Data;

class G_SendMessThread : public G_Thread
{
	public:
		/// @brief 构造函数
		G_SendMessThread();

		/// @brief 析构函数
		~G_SendMessThread();

		void Run();

		void addEpoll(int nSocket);

		void modEpoll(int nSocket);

		//void delEpoll(int nSocket);

		int sendMessage(int nSocket , const void *pStr);

	private:

		/// @brief epoll_create 返回文件描述符
		int epfd;

		struct epoll_event event[100] , ev;

		/// @brief 存放套接字和数据multimap
		multimap<int , std::string> g_sockDataMap;

		/// @brief multimap插入值
		typedef pair<int , std::string> g_mapPair;

		/// @brief 数据发送对象
		G_Data *g_data;
};

#endif
