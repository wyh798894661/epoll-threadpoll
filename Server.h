///
/// @file Server.h
/// @brief 服务器框架基类
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __SERVER__
#define __SERVER__

#include "def.h"

class G_Server
{
	public:

		/// @brief 析构函数
		virtual ~G_Server();

		/// @brief 初始化服务器程序字类需要继承这个函数
		///
		/// @return
		virtual bool init();

		/// @brief 结束服务器程序回收资源
	//	virtual void final() = 0;

	protected:

		/// @brief 构造函数
		G_Server();


	private:
		static G_Server *instance ;

};

#endif

