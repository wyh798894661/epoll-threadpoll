#ifndef __G_QUEUE__
#define __G_QUEUE__
///
/// @file Queue.h
/// @brief 队列的简单封装 , 队列操作时加了锁的保护
/// @author wangyuhang
/// @date 2016-03-21
///
#include "Lock.h"
#include "def.h"

template <class A>
class G_Queue
{
	public:
		/// @brief 构造函数
		///
		/// @param m_uQueSize 限制队列的大小, 如果m_uQueSize为0不限制队列的大小
		G_Queue(ULONG uQueSize = 0);

		/// @brief 析构函数
		~G_Queue();

		/// @brief 压一个元素入队列
		///
		/// @param item 一个元素
		///
		/// @return 如果为false 表示失败,如果为true表示成功
		bool push(const A &item);

		/// @brief 从对首弹出一个元素
		///
		/// @param item 存放在item
		///
		/// @return 如果为false 表示失败 ,如果为true表示成功
		bool pop(A &item);

		/// @brief 得到对首一个元素 , 但是不删除对首
		///
		/// @param item 存放在item
		///
		/// @return 如果为false 表示失败 , 如果为true表示成功
		bool getFront(A &item);

		/// @brief 判断队列是否为空
		///
		/// @return true为空队列 , false不为空队列
		bool isEmpty();

		/// @brief 清空队列
		void clear();

		/// @brief 去队列的大小
		///
		/// @return 队列的大小
		ULONG size();

		/// @brief 设置队列最大长度
		///
		/// @param maxSize 最大值
		///
		/// @return 如果maxSize 比m_uQueSize 小返回false , 否则返回true
		bool setQueueMaxSize(ULONG maxSize);

	private:

		deque<A> m_que;    ///STL 提供双向列表在插入和删除的操作中效率比vector高

		G_Lock m_lock;     ///读写锁

		ULONG m_uQueSize;   ///队列大小
};

template <class A>
G_Queue<A>::G_Queue(ULONG uQueSize)
{
	m_uQueSize = uQueSize;
}

template <class A>
G_Queue<A>::~G_Queue()
{
	m_que.clear();
}

template <class A>
bool G_Queue<A>::push(const A &item)
{
	m_lock.wLock();
	if(m_uQueSize && (m_que.size() == m_uQueSize))  ///如果限制队列大小才进行比较
	{
		m_lock.unwLock();
		return false;
	}

	m_que.push_back(item);
	m_lock.unwLock();
	return true;
}

template <class A>
bool G_Queue<A>::pop(A &item)
{
	m_lock.wLock();
	if(m_que.size() == 0)
	{
		m_lock.unwLock();
		return false;
	}

	item = m_que.front();
	m_que.pop_front();
	m_lock.unwLock();
	return true;
}

template <class A>
bool G_Queue<A>::getFront(A &item)
{
	m_lock.rLock();
	if(m_que.size() == 0)
	{
		m_lock.unwLock();
		return false;
	}
	item = m_que.front();
	m_lock.unrLock();
	return true;
}

template <class A>
bool G_Queue<A>::isEmpty()
{
	m_lock.rLock();
	bool bRet = m_que.empty();
	m_lock.unrLock();
	return bRet;
}

template <class A>
void G_Queue<A>::clear()
{
	m_lock.wLock();
	m_que.clear();
	m_lock.unwLock();
}

template <class A>
ULONG G_Queue<A>::size()
{
	m_lock.rLock();
	ULONG uSize = m_que.size();
	m_lock.unrLock();
	return uSize;
}

template <class A>
bool G_Queue<A>::setQueueMaxSize(ULONG maxSize)
{
	m_lock.wLock();
	if(maxSize <= m_uQueSize)
	{
		m_lock.unwLock();
		return false;
	}

	m_lock.unwLock();
	return true;
}
#endif
