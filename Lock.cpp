/// 
/// @file Lock.cpp
/// @brief 
/// @author guozhiming
/// @date 2007-04-11
/// 
#include "Lock.h"

G_Lock::G_Lock()
{
	pthread_mutex_init(&r_Mutex , NULL);
	pthread_mutex_init(&w_Mutex , NULL);
	pthread_cond_init(&condReadCounter , NULL);
	readCounter = 0;
}

G_Lock::~G_Lock()
{
	pthread_mutex_destroy(&r_Mutex);
	pthread_mutex_destroy(&w_Mutex);
	pthread_cond_destroy(&condReadCounter);
}

void G_Lock::rLock()
{
	pthread_mutex_lock(&w_Mutex);   //防止于写操作冲突
	pthread_mutex_lock(&r_Mutex);   //防止readCounter 冲突
	readCounter++;
	pthread_mutex_unlock(&w_Mutex);     ///写解锁
	pthread_mutex_unlock(&r_Mutex);     ///读解锁
}

void G_Lock::unrLock()
{
	pthread_mutex_lock(&r_Mutex);      ///读加锁
	readCounter--;
	if(0 == readCounter)
	{
		pthread_cond_signal(&condReadCounter);    //如果readCounter为0 , 表示已经没有读了，可以写
	}
	pthread_mutex_unlock(&r_Mutex);     ///读解锁
}

void G_Lock::wLock()
{
	pthread_mutex_lock(&w_Mutex);   ///写加锁
	pthread_mutex_lock(&r_Mutex);   ///读加锁
	if(0 == readCounter)   ///防止readCounter = 0而且没有调用过rLock()和unrLock()
	{
		pthread_mutex_unlock(&r_Mutex);    ///读解锁
		return ;
	}
	pthread_cond_wait(&condReadCounter , &r_Mutex);         //等待readCounter = 0 , 等待期间r_Mutex被解锁，有信号再加锁
	pthread_mutex_unlock(&r_Mutex);       ///读解锁
}

void G_Lock::unwLock()
{
	pthread_mutex_unlock(&w_Mutex);         //写解锁
}
