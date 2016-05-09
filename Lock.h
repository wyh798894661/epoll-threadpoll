///
/// @file Lock.h
/// @brief
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __LOCK__
#define __LOCK__
#include "def.h"

/// @brief 锁的基本操作   1：读操作的时候读锁可以并发 2：写操作的时候，独占操作
class G_Lock
{
	public:

		/// @brief 构造函数初始化互斥锁 , 条件变量
		G_Lock();

		/// @brief 析构函数释放互斥锁，和条件变量
		~G_Lock();

		/// @brief 读锁 readCounter++ , 锁住readCounter
		void rLock();

		/// @brief 解锁 readCounter-- , 如果readCounter = 0 , pthread_cond_signal通知
		void unrLock();

		/// @brief 写锁 如果readCounter不为0一直 pthread_cond_wait等待下去
		void wLock();

		/// @brief 解锁
		void unwLock();

	private:
		pthread_mutex_t r_Mutex;     ///读锁 ，锁住readCounter

		pthread_mutex_t w_Mutex;     ///锁住同步资源

		unsigned long readCounter;             ///条件变量如果为0通知(pthread_cond_signal)

		pthread_cond_t condReadCounter;
};


#endif
