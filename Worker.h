///
/// @file Worker.h
/// @brief 用户接口类
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __WORKER__
#define __WORKER__

#include "ThreadPool.h"

/// @brief 抽象类
class G_Worker
{
	public:
		/// @brief 构造函数
		G_Worker(unsigned int num);

		/// @brief 析构函数
		~G_Worker();

		/// @brief 服务器帮定端口
		///
		/// @param nPort 帮定端口
		///
		/// @return true表示成功 , false表示失败
		bool Bind(unsigned int nPort);

		/// @brief 存虚函数子类继承并实现逻辑
		///
		/// @param pStr 客户端发送的字符串
		virtual void recvMessage(void *pStr , int nSocket) = 0;

		/// @brief 发送数据到客户端
		///
		/// @param pStr 数据
		/// @param nSocket 发送到客户端的套接字
		//
		/// @return
		int sendMessage(int nSocket , const void *pStr);

	protected:

	private:
		G_ThreadPool *g_threadPool;
};

#endif
