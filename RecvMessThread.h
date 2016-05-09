///
/// @file TaskThread.h
/// @brief 任务类 , 接受client发的消息进行处理
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __TASKTHREAD__
#define __TASKTHREAD__

#include "def.h"
#include "Thread.h"
#include "ThreadPool.h"
#include "Queue.h"
#include "Data.h"

class G_ThreadPool;
class G_Data;

class G_RecvMessThread : public G_Thread
{
	public:
		/// @brief 构造函数
		G_RecvMessThread(G_ThreadPool *pool);

		/// @brief 析构函数
		~G_RecvMessThread();

		/// @brief 主线程运行
		void Run();

		/// @brief 填加套接字
		///
		/// @param nSocket 套接字
		void addSocket(int nSocket);

		/// @brief 获得连接的客户端数目
		///
		/// @return 数目
		unsigned int getCounter();

		/// @brief 		往队列中存放数据
		///
		/// @param pStr  数据
		///
		/// @return true 成功 , false 失败
		bool pushData(std::string pStr);

	private:

		/// @brief 设置套接口非阻塞模式
		///
		/// @param sockfd 套接口
		///
		/// @return true 成功 , false 失败
		bool setNonBlock(int sockfd);

		/// @brief epoll_create 返回文件描述符
		int epfd;

		struct epoll_event events[100];

		/// @brief 记录接受客户端数目
		unsigned int counter;

		/// @brief 线程池对象
		G_ThreadPool *g_threadPool;

		/// @brief 存放数据的队列
		G_Queue<std::string> g_dataBufferQueue;

		G_Data *g_data;
};

#endif
