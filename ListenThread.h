///
/// @file ListenThread.h
/// @brief 服务器监听线程
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __G_LISTENTHREAD__
#define __G_LISTENTHREAD__

#include "Thread.h"
#include "Socket.h"
#include "ThreadPool.h"

class G_ThreadPool;

class G_ListenThread : public G_Thread
{

	public:
		/// @brief 构造函数
		G_ListenThread(G_ThreadPool *pool);

		/// @brief 析构函数
		virtual ~G_ListenThread();

		/// @brief
		void Run();

		/// @brief 服务器帮定端口
		///
		/// @param nPort 帮定端口
		///
		/// @return true表示成功 , false表示失败
		bool Bind(unsigned int nPort);

	private:

		///套接口操作的对象
		G_Socket *g_socket;

		G_ThreadPool *g_threadPool;

};

#endif
