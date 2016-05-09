///
/// @file ThreadPool.h
/// @brief 线程池的实现 , 是个管理线程 , 负责调用每个线程之间的互相调用的关系
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __G_THREADPOOL__
#define __G_THREADPOOL__

#include "ListenThread.h"
#include "SendMessThread.h"
#include "Queue.h"
#include "RecvMessThread.h"
#include "Worker.h"

class G_ListenThread;
class G_SendMessThread;
class G_RecvMessThread;
class G_Worker;

class G_ThreadPool : public G_Thread
{
	public:
		/// @brief 构造函数
		G_ThreadPool(unsigned int num , G_Worker *g_work);

		/// @brief 析构函数
		~G_ThreadPool();

		/// @brief 服务器帮定端口
		///
		/// @param nPort 帮定端口
		///
		/// @return true表示成功 , false表示失败
		bool Bind(unsigned int nPort);

		/// @brief 主线程
		void Run();

		/// @brief 填加socket到队列中
		///
		/// @param nSocket 套接口
		///
		/// @return true 表示成功 , false 表示失败
		bool pushSocket(unsigned int nSocket);

		/// @brief 从队列中取套接字
		///
		/// @param nSocket 取出的套接字存放在nSocket中
		///
		/// @return true 表示成功 , false 表示失败
		bool popSocket(int &nSocket);

		/// @brief 从G_Data->G_RecvMessThread->G_ThreadPool->G_Worker 回掉
		///
		/// @param pStr 客户发的字符串
		/// @param nSocket 接受客户连接的套接字
		void recvMessage(void *pStr , int nSocket);

		/// @brief 发送数据 从testPool->G_Worker->G_ThreadPool->G_SendMessThread->G_Data
		///
		/// @param pStr 数据
		/// @param nSocket 套接口
		/// @return
		//
		int sendMessage(int nSocket , const void *pStr);

	private:

		G_Worker *g_worker;

		/// @brief 监听线程
		G_ListenThread *g_listenThread;

		/// @brief 发送消息线程
		G_SendMessThread *g_sendMessThread;

		/// @brief 存放socket队列
		G_Queue<int> g_sockQueue;

		/// @brief 存放空闲工作线程队列
		G_Queue<G_RecvMessThread*> g_idleRecvMessThreadQueue;

		/// @brief 存放忙碌工作线程队列
		G_Queue<G_RecvMessThread*> g_busyRecvMessThreadQueue;

		/// @brief 每个RecvMessThread线程中最大用户数
		static const int maxCounter = 2000;

		/// @brief 如果线程不够用新增加的线程
		static const int addTaskThread = 2;
};

#endif
