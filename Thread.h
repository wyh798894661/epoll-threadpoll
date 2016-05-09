///
/// @file Thread.h
/// @brief 线程的封装 , 子类继承并实现自己的功能
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __G_THREAD__
#define __G_THREAD__
#include "def.h"

class G_Thread
{
	public:
		/// @brief 构造函数
		G_Thread();

		/// @brief 析构函数
		~G_Thread();

		/// @brief 获得线程id
		///
		/// @return 线程id
		pthread_t getThreadId();

		/// @brief 启动线程
		bool Start();

		/// @brief 线程停止
		void pause();

		/// @brief 线程继续运行
		void continues();

	private:
		/// @brief  屏蔽SIGUSR1信号 , POSIX标准建议在调用sigwait()等待信号以前，进程中所有线程都应屏蔽该信号，以保证仅有sigwait()的调用者获得该信号 , 如果不屏蔽该信号，在sigwait()之前调用pthread_kill()就会出现User defined signal 1.
		void maskSIGUSR1();

		/// @brief 线程pid
		pthread_t g_pid;

		/// @brief 信号
		sigset_t g_waitSig;

		/// @brief 线程运行主函数
		///
		/// @param arg
		///
		/// @return
		static void *threadFun(void *arg);

	protected:
		virtual void Run() = 0;

};

#endif
