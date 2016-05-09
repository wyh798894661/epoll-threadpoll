///
/// @file Socket.h
/// @brief 套接口的简单封装
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __G_SOCKET__
#define __G_SOCKET__

#include "def.h"

class G_Socket
{
	public:
		/// @brief 构造函数
		G_Socket();

		/// @brief 析构函数
		~G_Socket();

		/// @brief 服务器帮定端口
		///
		/// @param nPort 帮定端口
		///
		/// @return true表示成功 , false表示失败
		bool Bind(unsigned int nPort);

		/// @brief 如果有client连接得到套接字
		///
		/// @param nSocket 返回套接字
		///
		/// @return true 表示获得套接字成功 , false 表示获得套接字失败
		bool Listen(int &nSocket);

	private:
		/// @brief 套接字
		int g_sockfd;

		/// @brief epoll_create 返回文件描述符
		int epfd;

		struct epoll_event events[100];

		/// @brief 设置套接口非阻塞模式
		///
		/// @param sockfd 套接口
		///
		/// @return true 成功 , false 失败
		bool setNonBlock(int sockfd);

};

#endif
